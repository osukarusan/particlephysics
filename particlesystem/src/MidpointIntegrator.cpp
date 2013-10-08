#include "MidpointIntegrator.h"

MidpointIntegrator::MidpointIntegrator(void)
{
}

MidpointIntegrator::~MidpointIntegrator(void)
{
}

void MidpointIntegrator::doStep(PhysicsSystem *system, float h) {
	
	Vecd x0   = system->getState();
	Vecd dx   = system->getDerivative();	
	double t0 = system->getTime();

	// Euler step
	Vecd xinc = h*dx;

	// evaluate at midpoint
	system->setState(x0 + 0.5*xinc);
	system->setTime (t0 + 0.5*h);
	Vecd fmid = system->getDerivative();
	
	// take a step using fmid
	Vecd x1 = x0 + h*fmid;
	system->setState(x1);
	system->setTime (t0 + h);

}