#include "RungeKuttaIntegrator.h"

RungeKuttaIntegrator::RungeKuttaIntegrator(void)
{
}

RungeKuttaIntegrator::~RungeKuttaIntegrator(void)
{
}

void RungeKuttaIntegrator::doStep(PhysicsSystem *system, float h) {
	
	Vecd   x0 = system->getState();
	double t0 = system->getTime();

	Vecd k1 = h*system->getDerivative();
	
	system->setState(x0 + 0.5*k1);
	system->setTime (t0 + 0.5*h);
	Vecd k2 = h*system->getDerivative();

	system->setState(x0 + 0.5*k2);
	system->setTime (t0 + 0.5*h);
	Vecd k3 = h*system->getDerivative();

	system->setState(x0 + k3);
	system->setTime(t0 + h);
	Vecd k4 = h*system->getDerivative();

	Vecd x1 = x0 + (k1 + k4)/6.0 + (k2 + k3)/3.0;
	system->setState(x1);
	system->setTime(t0 + h);

}
