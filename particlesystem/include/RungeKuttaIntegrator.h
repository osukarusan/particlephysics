#ifndef _RUNGE_KUTTA_INTEGRATOR_
#define _RUNGE_KUTTA_INTEGRATOR_

#include "Integrator.h"

class RungeKuttaIntegrator : public Integrator
{
public:

	RungeKuttaIntegrator();
	~RungeKuttaIntegrator();
	
	virtual void doStep(PhysicsSystem* system, float time);

};

#endif