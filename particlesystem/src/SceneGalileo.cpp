#include "SceneGalileo.h"
#include "ConstantForce.h"
#include "DataManager.h"
#include "defines.h"


SceneGalileo::SceneGalileo(void)
{
	m_GalileoAnalytic = 0;
	m_GalileoEuler = 0;
	m_GalileoRungeKutta = 0;
}

SceneGalileo::~SceneGalileo(void)
{
	if (m_GalileoAnalytic)   delete m_GalileoAnalytic;
	if (m_GalileoEuler)      delete m_GalileoEuler;
	if (m_GalileoRungeKutta) delete m_GalileoRungeKutta;
}


void SceneGalileo::init() {
	
	if (m_GalileoAnalytic)   delete m_GalileoAnalytic;
	if (m_GalileoEuler)      delete m_GalileoEuler;
	if (m_GalileoRungeKutta) delete m_GalileoRungeKutta;
	
	double h0 = DataManager::mInitialHeight;
	Particle* pAnalytic = new Particle(Vec3d(-4.0, h0, 0.0), Vec3d(0.0, 0.0, 0.0), 1.0);
	Particle* pEuler    = new Particle(Vec3d( 0.0, h0, 0.0), Vec3d(0.0, 0.0, 0.0), 1.0);
	Particle* pRunge    = new Particle(Vec3d( 4.0, h0, 0.0), Vec3d(0.0, 0.0, 0.0), 1.0);
	pAnalytic->color = Vec3f(1.0f, 0.0f, 0.0f);
	pEuler->color    = pRunge->color = Vec3f(0.0f, 0.0f, 1.0f);

	ConstantForce* fAnalytic = new ConstantForce();
	fAnalytic->addInfluencedParticle(pAnalytic);
	fAnalytic->setGravityConstant(Vec3d(0.0, -DataManager::mGravityValue, 0.0));
	ConstantForce* fEuler = new ConstantForce();
	fEuler->addInfluencedParticle(pEuler);
	fEuler->setGravityConstant(Vec3d(0.0, -DataManager::mGravityValue, 0.0));
	ConstantForce* fRunge = new ConstantForce();
	fRunge->addInfluencedParticle(pRunge);
	fRunge->setGravityConstant(Vec3d(0.0, -DataManager::mGravityValue, 0.0));

	m_GalileoAnalytic = new ParticleSystem();
	m_GalileoAnalytic->addParticle(pAnalytic);
	m_GalileoAnalytic->addForce(fAnalytic);
	m_GalileoEuler = new ParticleSystem();
	m_GalileoEuler->addParticle(pEuler);
	m_GalileoEuler->addForce(fEuler);
	m_GalileoRungeKutta = new ParticleSystem();
	m_GalileoRungeKutta->addParticle(pRunge);
	m_GalileoRungeKutta->addForce(fRunge);

	std::vector<Particle> vparts;
	vparts.push_back(*pAnalytic);
	vparts.push_back(*pEuler);
	vparts.push_back(*pRunge);
	DataManager::mParticles.push_back(vparts);

}

void SceneGalileo::update() {

	double h0 = DataManager::mInitialHeight;
	double G  = DataManager::mGravityValue;
	double t  = m_GalileoAnalytic->getTime() + DataManager::mTimeStep;
	Particle* pAnalytic = m_GalileoAnalytic->getParticle(0);
	pAnalytic->pos = Vec3d(-4.0, std::max(h0 - 0.5*G*t*t, 0.0), 0.0);
	m_GalileoAnalytic->setTime(t);

	m_Euler.doStep(m_GalileoEuler, DataManager::mTimeStep);
	Particle* pEuler = m_GalileoEuler->getParticle(0);
	pEuler->pos[1] = std::max(pEuler->pos[1], 0.0);

	m_RungeKutta.doStep(m_GalileoRungeKutta, DataManager::mTimeStep);
	Particle* pRunge = m_GalileoRungeKutta->getParticle(0);
	pRunge->pos[1] = std::max(pRunge->pos[1], 0.0);

	std::vector<Particle> vparts;
	vparts.push_back(*pAnalytic);
	vparts.push_back(*pEuler);
	vparts.push_back(*pRunge);
	DataManager::mParticles.push_back(vparts);

	/*std::cerr << pAnalytic->pos << "\t";
	std::cerr << pEuler->pos << "\t";
	std::cerr << pRunge->pos << std::endl << std::endl;*/

}