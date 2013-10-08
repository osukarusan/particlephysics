#include "SceneTinkertoy.h"
#include "DataManager.h"
#include "DampingForce.h"
#include "FixedDistanceConstraint.h"
#include "RigidJointConstraint.h"

SceneTinkertoy::SceneTinkertoy(void)
{
	m_system = 0;
	m_mouseSpring = 0;
}

SceneTinkertoy::~SceneTinkertoy(void)
{
}

void SceneTinkertoy::init() {

	if (m_system) delete m_system;
	
	Vec3d  wirePos = DataManager::mCircleWireCenter;
	double wireRad = DataManager::mCircleWireRadius;
	CircleWireConstraint* constraint = new CircleWireConstraint();
	constraint->setCenter(wirePos);
	constraint->setRadius(wireRad);

	Particle *particle = new Particle(Vec3d(-wireRad, 0, 0.0), Vec3d(0.0, 0.0, 0.0), 1.0);
	constraint->setParticle(particle);

	ConstantForce* gravity = new ConstantForce();
	gravity->addInfluencedParticle(particle);
	gravity->setGravityConstant(Vec3d(0.0, -DataManager::mGravityValue, 0.0));

	DampingForce* damp = new DampingForce();
	damp->addInfluencedParticle(particle);
	damp->setDampingCoefficient(DataManager::mDampCoeff);

	m_mouseSpring = new SpringForce();
	m_mouseSpring->setSpringCoefficient(DataManager::mMouseCoeff);

	m_system = new ConstrainedParticleSystem();
	m_system->addParticle(particle);
	m_system->addForce(gravity);
	m_system->addForce(damp);
	m_system->addForce(m_mouseSpring);
	m_system->addConstraint(constraint);

	for (int i = 0; i < DataManager::mInitExtraParticles.size(); i++) {
		Particle *p = new Particle(DataManager::mInitExtraParticles[i], Vec3d(0,0,0), 1.0);
		gravity->addInfluencedParticle(p);
		m_system->addParticle(p);
	}
	for (int i = 0; i < DataManager::mInitFixDistConstraints.size(); i++) {
		std::pair<int, int>& parts = DataManager::mInitFixDistConstraints[i];
		Particle *p1 = m_system->getParticle(parts.first);
		Particle *p2 = m_system->getParticle(parts.second);
		if (p1 && p2) {
			FixedDistanceConstraint *c = new FixedDistanceConstraint();
			c->setParticles(p1, p2);
			c->setDistance(len(p1->pos - p2->pos));
			m_system->addConstraint(c);
		}
	}
	

	std::vector<Particle> vparts;
	for (int i = 0; i < m_system->getNumParticles(); i++) {
		vparts.push_back(*m_system->getParticle(i));
	}
	DataManager::mParticles.push_back(vparts);

}

void SceneTinkertoy::update() {

	SpringForce force;
	if (DataManager::mSelectedParticle >= 0) {
		m_mouseSpring->setEquilibriumPoint(DataManager::mMouse3Dpos);
		m_mouseSpring->addInfluencedParticle(m_system->getParticle(DataManager::mSelectedParticle));
	}

	m_integrator.doStep(m_system, DataManager::mTimeStep);

	m_mouseSpring->clearInfluencedParticles();

	std::vector<Particle> vparts;
	for (int i = 0; i < m_system->getNumParticles(); i++) {
		vparts.push_back(*m_system->getParticle(i));
	}
	DataManager::mParticles.push_back(vparts);
	DataManager::mCenter.push_back(DataManager::mVolumeCenter);

}
