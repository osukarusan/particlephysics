#include "SceneFountain.h"
#include "DataManager.h"
#include <vector>


SceneFountain::SceneFountain(void)
{
	m_system = NULL;
	m_gravityForce = NULL;
	m_floor = NULL;
	m_ball = NULL;
}


SceneFountain::~SceneFountain(void)
{
	if (m_system)		delete m_system;
	if (m_floor)		delete m_floor;
	if (m_ball)			delete m_ball;
	m_system = NULL;
	m_gravityForce = NULL;
	m_floor = NULL;
	m_ball = NULL;
}

void SceneFountain::init(int numParticles) {
	
	if (m_system) delete m_system;
	m_system = new ParticleSystem();

	m_gravityForce = new ConstantForce();
	m_gravityForce->setGravityConstant(Vec3d(0.0, -DataManager::mGravityValue, 0.0));
	m_system->addForce(m_gravityForce);

	m_floor = new CollisionPlane();
	m_floor->setPlane(Vec3d(0,1,0), 0);

	m_ball = new CollisionSphere();
	m_ball->useInnerSide(false);
	m_ball->setPosition(Vec3d(0, 0.25*DataManager::mFountainHeight, 0));
	m_ball->setRadius(0.25);

	std::vector<Particle> vparts;
	double eps = DataManager::mCollisionEpsilon;

	for (int i = 0; i < numParticles; i++) {
		Vec3d pp(0, DataManager::mFountainHeight, 0);
		Vec3d pv(2*random01() - 1, -0.5*random01(), 2*random01() - 1);

		Particle* p = new Particle(pp, pv, 1.0);
		p->color = Vec3f(0, 1.0, 1.0);
		m_system->addParticle(p);
		vparts.push_back(*p);
	}

	DataManager::mParticles.push_back(vparts);
	DataManager::mCenter.push_back(Vec3d(0, 0.25*DataManager::mFountainHeight, 0));
	DataManager::mBallCenter = Vec3d(0, 0.25*DataManager::mFountainHeight, 0);

	m_totalTime = 0.0;
	m_initParticles = 0;
}

void SceneFountain::update() {

	// init some particles until all of them are active
	int activeParts = std::min(m_system->getNumParticles(), m_initParticles + 10);
	for (int i = m_initParticles; i < activeParts; i++) {
		m_gravityForce->addInfluencedParticle(m_system->getParticle(i));
	}
	for (int i = activeParts; i < m_system->getNumParticles(); i++) {
		m_system->getParticle(i)->pos = Vec3d(0, DataManager::mFountainHeight, 0);
	}
	m_initParticles = activeParts;

	// update ball position
	Vec3d ballPos = m_ball->getPosition();
	ballPos[0] = 0.5*std::sin(m_totalTime*5);
	m_ball->setPosition(ballPos);
	DataManager::mBallCenter = ballPos;

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

			// restart condition: small velocity
			if (abs(p->vel[1]) < 0.2*DataManager::mFountainHeight) {
				p->pos = Vec3d(0, DataManager::mFountainHeight, 0);
				p->vel = Vec3d(random01() - 0.5, 0, 0.5*random01());
			}
		}
	}

	// update data manager (needed for replay)
	std::vector<Particle> vparts;
	for (int i = 0; i < m_system->getNumParticles(); i++) {
		vparts.push_back(*m_system->getParticle(i));
	}
	DataManager::mParticles.push_back(vparts);
	DataManager::mCenter.push_back(DataManager::mBallCenter);

	m_totalTime += DataManager::mTimeStep;

}

