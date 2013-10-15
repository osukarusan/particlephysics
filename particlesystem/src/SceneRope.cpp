#include "SceneRope.h"
#include "DataManager.h"


SceneRope::SceneRope(void)
{
	m_system = NULL;
	m_ball   = NULL;
	m_floor  = NULL;
	m_gravityForce = NULL;
}


SceneRope::~SceneRope(void)
{
	if (m_system)		delete m_system;
	if (m_ball)			delete m_ball;
	if (m_floor)		delete m_floor;
	m_system = NULL;
	m_ball   = NULL;
	m_gravityForce = NULL;
}

void SceneRope::init() {

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

	std::vector<Particle> vparts;
	double eps = DataManager::mCollisionEpsilon;
	for (int i = 0; i < DataManager::mRopeParticles; i++) {
		Vec3d pp(double(i)/10.0, 3, 0);
		Vec3d pv(0, 0, 0);
		Particle* p = new Particle(pp, pv, 1.0);
		p->color = Vec3f(random01(), random01(), random01());
		m_system->addParticle(p);
		vparts.push_back(*p);

		if (i > 0) {
			m_gravityForce->addInfluencedParticle(p);

			Particle* p2 = m_system->getParticle(i-1);
			MassSpringForce* msf = new MassSpringForce();
			msf->setParticlePair(p2, p);
			msf->setRestingLength(len(p2->pos - p->pos));
			msf->setSpringCoefficient(DataManager::mSpringK);
			msf->setDampingCoefficient(DataManager::mSpringDamp);
			m_system->addForce(msf);
		}
		else {
			p->mass = 1e32;
		}
	}

	DataManager::mParticles.push_back(vparts);

}

void SceneRope::update() {

	// integration step
	m_integrator.doStep(m_system, DataManager::mTimeStep);

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
			p->vel = kt*velT - kr*velN;
			p->pos = p->pos - (1 + kr)*(dot(nor, p->pos) + m_floor->getK())*nor + eps*nor;
		}
	}

	// update data manager (needed for replay)
	std::vector<Particle> vparts;
	for (int i = 0; i < m_system->getNumParticles(); i++) {
		vparts.push_back(*m_system->getParticle(i));
	}
	DataManager::mParticles.push_back(vparts);
	
	//m_totalTime += DataManager::mTimeStep;

}

void SceneRope::moveBall(const Vec3d& d) {
	m_ball->move(d);
	DataManager::mSpringBall = m_ball->getPosition();
}
