#include "ConstantForce.h"

ConstantForce::ConstantForce(void)
{
	G = Vec3d(0.0, -9.81, 0.0);
}

ConstantForce::~ConstantForce(void)
{
}

void ConstantForce::apply() {
	std::vector<Particle*>::iterator it;
	for (it = m_particles.begin(); it != m_particles.end(); it++) {
		// F = m G
		(*it)->force += (*it)->mass * G;
	}
}
