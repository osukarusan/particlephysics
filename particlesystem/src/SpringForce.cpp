#include "SpringForce.h"

SpringForce::SpringForce(void)
{
	m_kd = 1.0;
	m_ks = 0.0;
	m_equilibrium = Vec3d(0,0,0);
}

SpringForce::~SpringForce(void)
{
}

void SpringForce::apply() {
	std::vector<Particle*>::iterator it;
	for (it = m_particles.begin(); it != m_particles.end(); it++) {
		Vec3d  dir = (*it)->pos - m_equilibrium;
		double Dx  = len(dir);
		if (Dx > 0) {
			dir.Normalise();
			double drag = -m_ks*Dx;
			double damp = -m_kd*(dot((*it)->vel, dir));
			(*it)->force += (drag + damp)*dir;
		}
	}
}