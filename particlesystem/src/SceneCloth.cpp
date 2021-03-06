#include "SceneCloth.h"
#include "DataManager.h"


SceneCloth::SceneCloth(void)
{
	m_system = NULL;
	m_ball   = NULL;
	m_floor  = NULL;
	m_gravityForce = NULL;
}


SceneCloth::~SceneCloth(void)
{
	if (m_system)		delete m_system;
	if (m_ball)			delete m_ball;
	if (m_floor)		delete m_floor;
	m_springs.clear();
	m_system = NULL;
	m_ball   = NULL;
	m_gravityForce = NULL;
}


MassSpringForce* createSpring(Particle* p1, Particle* p2, double multiplier = 1.0) {
	MassSpringForce* msf = new MassSpringForce();
	msf->setParticlePair(p2, p1);
	msf->setRestingLength(len(p2->pos - p1->pos));
	msf->setSpringCoefficient(DataManager::mSpringK*multiplier);
	msf->setDampingCoefficient(DataManager::mSpringDamp);
	return msf;
}


void SceneCloth::init() {

	if (m_system) delete m_system;
	m_system = new ParticleSystem();

	m_gravityForce = new ConstantForce();
	m_gravityForce->setGravityConstant(Vec3d(0.0, -DataManager::mGravityValue, 0.0));
	m_system->addForce(m_gravityForce);

	m_floor = new CollisionPlane();
	m_floor->setPlane(Vec3d(0,1,0), 0);

	m_ball = new CollisionSphere();
	m_ball->useInnerSide(false);
	m_ball->setPosition(DataManager::mSpringBall);
	m_ball->setRadius(DataManager::mSpringBallRadius);
	
	int N = DataManager::mRopeParticles;
	std::vector<Particle> vparts;
	double eps = DataManager::mCollisionEpsilon;
	double iniz = (DataManager::mFixedCloth ? 0 : 0.05*N); 

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Vec3d pp(0.1*j - 0.05*N, 3, -0.1*i + iniz);
			Vec3d pv(0, 0, 0);
			Particle* p = new Particle(pp, pv, 1.0);
			p->color = Vec3f(random01(), random01(), random01());
			m_system->addParticle(p);
			vparts.push_back(*p);

			if (i > 0 || !DataManager::mFixedCloth) {
				m_gravityForce->addInfluencedParticle(p);
			}
			else {
				p->mass = 1e32;
			}
		}
	}

	m_springs.clear();
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < N - 1; j++) {
			Particle* p = m_system->getParticle(i*N + j);
			double multiplier = 1.0;

			// bend
			if (DataManager::mBendingCloth) {
				if (i >= 2)		m_springs.push_back(createSpring(p, m_system->getParticle((i-2)*N + j)));
				else			multiplier *= 2.0;
				if (i < N-2)	m_springs.push_back(createSpring(p, m_system->getParticle((i+2)*N + j)));
				else			multiplier *= 2.0;
				if (j >= 2)		m_springs.push_back(createSpring(p, m_system->getParticle(i*N + j - 2)));
				else			multiplier *= 2.0;
				if (j < N-2)	m_springs.push_back(createSpring(p, m_system->getParticle(i*N + j + 2)));
				else			multiplier *= 2.0;
			}

			// stretch
			m_springs.push_back(createSpring(p, m_system->getParticle((i-1)*N + j), multiplier));
			m_springs.push_back(createSpring(p, m_system->getParticle((i+1)*N + j), multiplier));
			m_springs.push_back(createSpring(p, m_system->getParticle(i*N + j - 1), multiplier));
			m_springs.push_back(createSpring(p, m_system->getParticle(i*N + j + 1), multiplier));

			// shear
			m_springs.push_back(createSpring(p, m_system->getParticle((i-1)*N + j - 1), multiplier));
			m_springs.push_back(createSpring(p, m_system->getParticle((i-1)*N + j + 1), multiplier));
			m_springs.push_back(createSpring(p, m_system->getParticle((i+1)*N + j - 1), multiplier));
			m_springs.push_back(createSpring(p, m_system->getParticle((i+1)*N + j + 1), multiplier));
		}
	}
	for (unsigned int i = 0; i < m_springs.size(); i++)
		m_system->addForce(m_springs[i]);

	DataManager::mParticles.push_back(vparts);

}

void SceneCloth::update() {
	
	// integration step
	m_integrator.doStep(m_system, DataManager::mTimeStep);
	
	// position correction
	for (int iter = 0; iter < 3; iter++)
		for (unsigned int i = 0; i < m_springs.size(); i++)
			m_springs[m_springs.size() - 1 - i]->correctPosition();

	// collision detection and response
	double kr  = DataManager::mCoeffRestitution;
	double kt  = DataManager::mTangentialFriction;
	double eps = DataManager::mCollisionEpsilon;

	for (int i = 0; i < m_system->getNumParticles(); i++) {
		Particle *p = m_system->getParticle(i);
		Vec3d pos, nor;

		// sphere collision
		if (m_ball && m_ball->testCollision(p, eps, pos, nor))
		{
			Vec3d velN = dot(nor, p->vel)*nor;
			Vec3d velT = p->vel - velN;
			p->vel = kt*velT - kr*velN;
			p->pos = p->pos - (1 + kr)*(dot(nor, p->pos) - dot(nor, pos))*nor + eps*nor;
		}

		// plane collision
		if (m_floor->testCollision(p, eps, pos, nor)) {
			Vec3d velN = dot(nor, p->vel)*nor;
			Vec3d velT = p->vel - velN;
			p->vel = 0*velT - kr*velN;
			p->pos = p->pos - (1 + kr)*(dot(nor, p->pos) + m_floor->getK())*nor + eps*nor;
		}
	}
	
	// update data manager (needed for replay)
	std::vector<Particle> vparts;
	for (int i = 0; i < m_system->getNumParticles(); i++) {
		vparts.push_back(*m_system->getParticle(i));
	}
	DataManager::mParticles.push_back(vparts);
	
}

void SceneCloth::moveBall(const Vec3d& d) {
	m_ball->move(d);
	DataManager::mSpringBall = m_ball->getPosition();
}

