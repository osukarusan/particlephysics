#include "SceneSnow.h"
#include "ConstantForce.h"
#include "DataManager.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "defines.h"
#include <set>


SceneSnow::SceneSnow(void)
{
	m_system = NULL;
	m_boundingVolume = NULL;
}

SceneSnow::~SceneSnow(void)
{
}


void SceneSnow::init(int numParticles, bool cube) {

	const double PI = 3.14159265358979323846;
	srand(1);

	if (m_system) delete m_system;
	m_system = new ParticleSystem();

	m_gravityForce = new ConstantForce();
	m_gravityForce->setGravityConstant(Vec3d(0.0, -DataManager::mGravityValue, 0.0));
	m_system->addForce(m_gravityForce);
	m_contactForce = new ConstantForce();
	m_contactForce->setGravityConstant(Vec3d(0.0,  DataManager::mGravityValue, 0.0));
	m_system->addForce(m_contactForce);

	if (!cube) {
		CollisionSphere* ct = new CollisionSphere();
		ct->useInnerSide(true);
		this->setCollisionTest(ct);
	}
	else {
		CollisionAABB* ct = new CollisionAABB();
		ct->useInnerSide(true);
		this->setCollisionTest(ct);
	}
	
	m_volumeMovement = Vec3d(0,0,0);
	m_shakeVolume = false;
	DataManager::mVolumeCenter = Vec3d(0,0,0);

	std::vector<Particle> vparts;

	double eps = DataManager::mCollisionEpsilon;

	for (int i = 0; i < numParticles; i++) {
		double xp = std::min(std::max(-1 + 2*eps, (rand()%1024)/512.0 - 1.0), 1.0 - 2*eps);
		double yp = std::min(std::max(-1 + 2*eps, (rand()%1024)/512.0 - 1.0), 1.0 - 2*eps);
		double zp = std::min(std::max(-1 + 2*eps, (rand()%1024)/512.0 - 1.0), 1.0 - 2*eps);
		Vec3d pos = Vec3d(xp, yp, zp);
		if (!cube) {
			double r = std::max(std::min((rand()%1024)/1024.0, 1.0 - 2*eps), 2*eps);
			pos.Normalise();
			pos = r*pos;
		}
		Particle* p = new Particle(pos, Vec3d(0.0, 0.0, 0.0), 1.0);
		p->color = Vec3f((rand()%1024)/1024.0f, (rand()%1024)/1024.0f, (rand()%1024)/1024.0f);
		m_gravityForce->addInfluencedParticle(p);
		m_system->addParticle(p);
		vparts.push_back(*p);
	}

	DataManager::mParticles.push_back(vparts);
	DataManager::mCenter.push_back(Vec3d(0,0,0));

}


void SceneSnow::update() {

	// if volume's been shaked, update movement
	if (m_shakeVolume) {
		updateVolumeShake();
		m_volumeMovement = Vec3d(0,0,0);
		m_shakeVolume = false;
	}

	// integration step
	m_integrator.doStep(m_system, DataManager::mTimeStep);

	// clear contact forces
	m_contactForce->clearInfluencedParticles();

	// collision detection and response, maybe add contact forces
	double kr  = DataManager::mCoeffRestitution;
	double kt  = DataManager::mTangentialFriction;
	double eps = DataManager::mCollisionEpsilon;
	for (int i = 0; i < m_system->getNumParticles(); i++) {
		Particle *p = m_system->getParticle(i);
		Vec3d pos, nor;
		if (m_boundingVolume->testCollision(p, eps, pos, nor)) {
			Vec3d velN = dot(nor, p->vel)*nor;
			Vec3d velT = p->vel - velN;
			p->vel = kt*velT - kr*velN;
			p->pos = pos + eps*nor;
			// contact condition: collision with the floor and a velocity so small
			// that gravity would make the particle penetrate it
			if (nor[1] > 0 && p->vel[1] < 0.5*DataManager::mTimeStep*DataManager::mGravityValue) {
				p->vel[1] = 0.5*DataManager::mTimeStep*DataManager::mGravityValue;
				m_contactForce->addInfluencedParticle(p);
			}
		}
	}

	// particle-particle collision
	if (DataManager::mParticleColl) {
		particlesCollisionTest();
	}

	// update data manager (needed for replay)
	std::vector<Particle> vparts;
	for (int i = 0; i < m_system->getNumParticles(); i++) {
		vparts.push_back(*m_system->getParticle(i));
	}
	DataManager::mParticles.push_back(vparts);
	DataManager::mCenter.push_back(DataManager::mVolumeCenter);

}


void SceneSnow::updateVolumeShake() {

	m_boundingVolume->move(m_volumeMovement);
	m_contactForce->clearInfluencedParticles();

	double kr  = DataManager::mCoeffRestitution;
	double eps = DataManager::mCollisionEpsilon;
	for (int i = 0; i < m_system->getNumParticles(); i++) {
		Particle *p = m_system->getParticle(i);
		Vec3d pos, nor;
		if (m_boundingVolume->testCollision(p, eps, pos, nor)) {
			Vec3d velN = dot(nor, p->vel)*nor;
			Vec3d velT = p->vel - velN;
			p->vel = velT - velN + 0.1*m_volumeMovement/DataManager::mTimeStep;
			p->pos = pos + eps*nor;
		}
	}

	DataManager::mVolumeCenter += m_volumeMovement;
}


void SceneSnow::particlesCollisionTest() {

	// Acceleration structure: regular grid
	std::vector<std::vector<Particle*> > grid;
	grid.resize(8*8*8); //512 cells
	std::set<int> occupiedCells;

	Vec3d bmin, bmax, cellsize;
	m_boundingVolume->getBoundingBox(bmin, bmax);
	cellsize = (bmax - bmin)/8;
	for (int i = 0; i < m_system->getNumParticles(); i++) {
		Particle* particle = m_system->getParticle(i);
		Vec3d p = particle->pos - bmin;
		int cellid =   int(p[0]/cellsize[0])
					 + int(p[1]/cellsize[1])*8
					 + int(p[2]/cellsize[2])*64;
		if (cellid < 0 || cellid >= 512) continue; //numerical stability issues 
		grid[cellid].push_back(particle);
		occupiedCells.insert(cellid);
	}

	// Now visit occupied cells and check particle collisions within
	double eps = DataManager::mCollisionEpsilon;
	double kr  = DataManager::mCoeffRestitution;
	std::set<int>::iterator it;
	for (it = occupiedCells.begin(); it != occupiedCells.end(); it++) {
		const std::vector<Particle*>& v = grid[*it];
		if (v.size() > 1) {
			for (int i = 0; i < v.size(); i++) {
				for (int j = i+1; j < v.size(); j++) {
					Vec3d  dir   = v[j]->pos - v[i]->pos;
					double dist2 = sqrlen(dir);
					if (dist2 < 4*eps*eps) {
						// collision response: velocity reflection respect centers direction
						dir.Normalise();
						v[i]->vel -= 2*dir*(dot(dir, v[i]->vel));
						v[j]->vel -= 2*dir*(dot(dir, v[j]->vel));
					}
				}
			}
		}
	}

}
