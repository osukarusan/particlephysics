#ifndef _SCENE_SNOW_
#define _SCENE_SNOW_

#include "ParticleSystem.h"
#include "RungeKuttaIntegrator.h"
#include "CollisionTest.h"
#include "ConstantForce.h"

class SceneSnow
{
public:
	SceneSnow(void);
	~SceneSnow(void);

	void init(int numParticles, bool cube = true);
	void update();

	void setCollisionTest(CollisionTest* ct);

	void shakeVolume(const Vec3d& v);
	
private:

	ParticleSystem*		 m_system;

	ConstantForce*		 m_gravityForce;
	ConstantForce*		 m_contactForce;
	CollisionTest*       m_boundingVolume;
	RungeKuttaIntegrator m_integrator;

	Vec3d	m_volumeMovement;
	bool	m_shakeVolume;

	void updateVolumeShake();
	void particlesCollisionTest();

};

inline void SceneSnow::setCollisionTest(CollisionTest* ct) {
	if (m_boundingVolume) delete m_boundingVolume;
	m_boundingVolume = ct;
}

inline void SceneSnow::shakeVolume(const Vec3d &v) {
	m_shakeVolume = true;
	m_volumeMovement += v;
}

#endif