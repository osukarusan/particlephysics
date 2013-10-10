#ifndef _SCENE_CLOTH_
#define _SCENE_CLOTH_

#include "ParticleSystem.h"
#include "VerletIntegrator.h"
#include "CollisionSphere.h"

class SceneCloth
{
public:

	SceneCloth(void);
	~SceneCloth(void);
	
	void init();
	void update();

private:

	ParticleSystem*		m_system;
	VerletIntegrator    m_integrator;


};

#endif