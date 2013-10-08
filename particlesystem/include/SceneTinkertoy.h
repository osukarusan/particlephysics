#ifndef _SCENE_TINKERTOY_
#define _SCENE_TINKERTOY_

#include "ConstrainedParticleSystem.h"
#include "RungeKuttaIntegrator.h"
#include "CircleWireConstraint.h"
#include "SpringForce.h"

class SceneTinkertoy
{
public:

	SceneTinkertoy(void);
	~SceneTinkertoy(void);
	
	void init();
	void update();

private:

	ConstrainedParticleSystem* m_system;
	RungeKuttaIntegrator       m_integrator;

	SpringForce*	m_mouseSpring;

};

#endif