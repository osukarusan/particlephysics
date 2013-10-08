#ifndef _MIDPOINT_INTEGRATOR_
#define _MIDPOINT_INTEGRATOR_ 

#include "Integrator.h"

class MidpointIntegrator : public Integrator
{
public:

	MidpointIntegrator(void);
	~MidpointIntegrator(void);

	virtual void doStep(PhysicsSystem* system, float time);

};

#endif