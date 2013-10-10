#ifndef _SCENE_ROPE_
#define _SCENE_ROPE_

#include "ParticleSystem.h"
#include "VerletIntegrator.h"
#include "RungeKuttaIntegrator.h"
#include "CollisionSphere.h"
#include "CollisionPlane.h"
#include "ConstantForce.h"
#include "MassSpringForce.h"

class SceneRope
{
public:

	SceneRope(void);
	~SceneRope(void);
	
	void init();
	void update();

	void moveBall(const Vec3d& d);

private:

	ParticleSystem*			m_system;
	RungeKuttaIntegrator    m_integrator;
	
	CollisionSphere*	m_ball;
	CollisionPlane*		m_floor;
	ConstantForce*		m_gravityForce;
	std::vector<MassSpringForce*> m_springs;

};

#endif