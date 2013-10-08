#ifndef _SCENE_FOUNTAIN_
#define _SCENE_FOUNTAIN_

#include "ParticleSystem.h"
#include "RungeKuttaIntegrator.h"
#include "ConstantForce.h"
#include "CollisionPlane.h"
#include "CollisionSphere.h"
#include "CollisionAABB.h"

class SceneFountain
{
public:
	SceneFountain(void);
	~SceneFountain(void);

	void init(int numParticles);
	void update();

private:

	ParticleSystem*		 m_system;

	ConstantForce*		 m_gravityForce;
	CollisionPlane*      m_floor;
	CollisionSphere*     m_ball;
	RungeKuttaIntegrator m_integrator;

	double  m_totalTime;
	int		m_initParticles;

};

#endif