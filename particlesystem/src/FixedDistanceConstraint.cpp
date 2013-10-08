#include "FixedDistanceConstraint.h"

FixedDistanceConstraint::FixedDistanceConstraint(void)
{
	m_distance = 0;
}

FixedDistanceConstraint::~FixedDistanceConstraint(void)
{
}


Vecd FixedDistanceConstraint::getConstraint() {
	// C(x, y, z) = (x1 - x2)^2 + (y1 - y2)^2 + (z1 - z2)^2 - r^2 = 0
	Vecd res(1);
	res[0] = sqrlen(m_particle1->pos - m_particle2->pos) - m_distance*m_distance;
	return res;
}

Vecd FixedDistanceConstraint::getDerivative() {
	// dC(x, y, z)/dt = dC/dx * dx/dt = 2*(x1 - x2, y1 - y2, z1 - z2)*(v1 - v2)
	Vecd res(1);
	Vec3d dp   = m_particle1->pos - m_particle2->pos;
	Vec3d dCdx(2*dp[0], 2*dp[1], 2*dp[2]);
	Vec3d dxdt = m_particle1->vel - m_particle2->vel;
	res[0] = dot(dCdx, dxdt);
	return res;
}

void FixedDistanceConstraint::computeGradient(Matd& jacobian, int row) {
	int col1 = 3*m_particle1->id;
	int col2 = 3*m_particle2->id;
	Vec3d p  = m_particle1->pos - m_particle2->pos;
	jacobian[row][col1]     =  2*p[0];
	jacobian[row][col1 + 1] =  2*p[1];
	jacobian[row][col1 + 2] =  2*p[2];
	jacobian[row][col2]     = -2*p[0];
	jacobian[row][col2 + 1] = -2*p[1];
	jacobian[row][col2 + 2] = -2*p[2];
}

void FixedDistanceConstraint::computeGradientDerivative(Matd& jacobianDeriv, int row) {
	int col1 = 3*m_particle1->id;
	int col2 = 3*m_particle2->id;
	Vec3d p = m_particle1->vel - m_particle2->vel;
	jacobianDeriv[row][col1]     =  2*p[0];
	jacobianDeriv[row][col1 + 1] =  2*p[1];
	jacobianDeriv[row][col1 + 2] =  2*p[2];
	jacobianDeriv[row][col2]     = -2*p[0];
	jacobianDeriv[row][col2 + 1] = -2*p[1];
	jacobianDeriv[row][col2 + 2] = -2*p[2];
}
