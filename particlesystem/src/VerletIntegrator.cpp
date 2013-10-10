#include "VerletIntegrator.h"


VerletIntegrator::VerletIntegrator(void)
{
	m_damping = 1;
}


VerletIntegrator::~VerletIntegrator(void)
{
}

void VerletIntegrator::doStep(PhysicsSystem *system, float h) {
	
	Vecd   xp = system->getPreviousState();
	Vecd   x0 = system->getState();
	Vecd   xd = system->getSecondDerivative();
	double t0 = system->getTime();

	Vecd   x1 = x0 + m_damping*(x0 - xp) + h*h*xd;

	system->setPreviousState(x0);
	system->setState(x1);
	system->setTime(t0 + h);

}
