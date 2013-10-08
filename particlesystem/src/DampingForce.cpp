#include "DampingForce.h"

DampingForce::DampingForce(void)
{
	m_kd = 0;
}

DampingForce::~DampingForce(void)
{
}

void DampingForce::apply() {
	std::vector<Particle*>::iterator it;
	for (it = m_particles.begin(); it != m_particles.end(); it++) {
		(*it)->force += -m_kd*(*it)->vel;
	}
}