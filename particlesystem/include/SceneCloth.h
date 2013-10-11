#ifndef _SCENE_CLOTH_
#define _SCENE_CLOTH_

#include "ParticleSystem.h"
#include "VerletIntegrator.h"
#include "RungeKuttaIntegrator.h"
#include "CollisionSphere.h"
#include "CollisionPlane.h"
#include "ConstantForce.h"
#include "MassSpringForce.h"

class SceneCloth
{
public:

	SceneCloth(void);
	~SceneCloth(void);

	void init();
	void update();
	
	void moveBall(const Vec3d& d);

private:

	ParticleSystem*		m_system;
	VerletIntegrator    m_integrator;
	
	CollisionSphere*	m_ball;
	CollisionPlane*		m_floor;
	ConstantForce*		m_gravityForce;
	std::vector<MassSpringForce*> m_springs;


};

#endif