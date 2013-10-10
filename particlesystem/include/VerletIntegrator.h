#ifndef _VERLET_INTEGRATOR_
#define _VERLET_INTEGRATOR_

#include "Integrator.h"

class VerletIntegrator : public Integrator
{
public:
	VerletIntegrator();
	~VerletIntegrator();

	void setDamping(double kd);
	
	virtual void doStep(PhysicsSystem* system, float time);

private:
	double m_damping;

};

inline void VerletIntegrator::setDamping(double kd) {
	m_damping = kd;
}	

#endif
