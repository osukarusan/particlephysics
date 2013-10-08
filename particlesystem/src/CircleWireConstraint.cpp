#include "CircleWireConstraint.h"

CircleWireConstraint::CircleWireConstraint(void)
{
	m_center = Vec3d(0,0,0);
	m_radius = 1.0;
}

CircleWireConstraint::~CircleWireConstraint(void)
{
}

Vecd CircleWireConstraint::getConstraint() {
	// C(x, y, z) = x^2 + y^2 + z^2 - r^2 = 0
	Vecd res(1);
	res[0] = sqrlen(m_particle->pos - m_center) - m_radius*m_radius;
	return res;
}

Vecd CircleWireConstraint::getDerivative() {
	// dC(x, y, z)/dt = dC/dx * dx/dt = (2x, 2y, 2z)*v
	Vecd res(1);
	Vec3d p = m_particle->pos - m_center;
	Vec3d dCdx(2*p[0], 2*p[1], 2*p[2]);
	res[0] = dot(dCdx, m_particle->vel); 
	return res;
}

void CircleWireConstraint::computeGradient(Matd& jacobian, int row) {
	int col = 3*m_particle->id;
	Vec3d p = m_particle->pos - m_center;
	jacobian[row][col]     = 2*p[0];
	jacobian[row][col + 1] = 2*p[1];
	jacobian[row][col + 2] = 2*p[2];
}

void CircleWireConstraint::computeGradientDerivative(Matd& jacobianDeriv, int row) {
	Vec3d p = m_particle->vel;
	int col = 3*m_particle->id;
	jacobianDeriv[row][col]     = 2*p[0];
	jacobianDeriv[row][col + 1] = 2*p[1];
	jacobianDeriv[row][col + 2] = 2*p[2];
}
