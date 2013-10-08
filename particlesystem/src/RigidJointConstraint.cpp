#include "RigidJointConstraint.h"

RigidJointConstraint::RigidJointConstraint(void)
{
}

RigidJointConstraint::~RigidJointConstraint(void)
{
}

Vecd RigidJointConstraint::getConstraint() {
	// C(x1, x2) = (x1 - c)*(x2 - c) - product = 0
	Vecd res(2);
	Vec3d p1 = m_particle1->pos - m_center;
	Vec3d p2 = m_particle2->pos - m_center;
	p1.Normalise();
	p2.Normalise();
	res[0] = dot(p1, p2) - m_product;
	// Fixed distance
	res[1] = sqrlen(m_particle1->pos - m_particle2->pos) - m_distance*m_distance;
	return res;
}

inline Vec3d derivNormVector(const Vec3d& p, const Vec3d& v) {
	double dotpp = dot(p, p);
	return (v*sqrt(dotpp) - p*(1/sqrt(dotpp))*dot(v,p))/dotpp;
}

Vecd RigidJointConstraint::getDerivative() {
	// dC(x1, x2)/dt = v1*(x2 - c) + (x1 - c)*v2 = 0
	Vecd res(2);
	Vec3d p1 = m_particle1->pos - m_center;
	Vec3d p2 = m_particle2->pos - m_center;
	//res[0] = dot(m_particle1->vel, p2) + dot(p1, m_particle2->vel);

	Vec3d der1 = derivNormVector(p1, m_particle1->vel);
	Vec3d der2 = derivNormVector(p2, m_particle2->vel);
	p1.Normalise();
	p2.Normalise();
	res[0] = dot(der1, p2) + dot(p1, der2);

	// Fixed distance
	Vec3d dp   = m_particle1->pos - m_particle2->pos;
	Vec3d dCdx(2*dp[0], 2*dp[1], 2*dp[2]);
	Vec3d dxdt = m_particle1->vel - m_particle2->vel;
	res[1] = dot(dCdx, dxdt);
	return res;
}

void RigidJointConstraint::computeGradient(Matd& jacobian, int row) {
	int col1 = 3*m_particle1->id;
	int col2 = 3*m_particle2->id;
	Vec3d p1 = m_particle1->pos - m_center;
	Vec3d p2 = m_particle2->pos - m_center;
	Vec3d n1 = p1;  n1.Normalise(); 
	Vec3d n2 = p2;  n2.Normalise();
	jacobian[row][col1]     = (sqrlen(p1) - p1[0]*p1[0])/(sqrlen(p1)*len(p1))*n2[0];
	jacobian[row][col1 + 1] = (sqrlen(p1) - p1[1]*p1[1])/(sqrlen(p1)*len(p1))*n2[1];
	jacobian[row][col1 + 2] = (sqrlen(p1) - p1[2]*p1[2])/(sqrlen(p1)*len(p1))*n2[2];
	jacobian[row][col2]     = (sqrlen(p2) - p2[0]*p2[0])/(sqrlen(p2)*len(p2))*n1[0];
	jacobian[row][col2 + 1] = (sqrlen(p2) - p2[1]*p2[1])/(sqrlen(p2)*len(p2))*n1[1];
	jacobian[row][col2 + 2] = (sqrlen(p2) - p2[2]*p2[2])/(sqrlen(p2)*len(p2))*n1[2];

	/*
	jacobian[row][col1]     = p2[0];
	jacobian[row][col1 + 1] = p2[1];
	jacobian[row][col1 + 2] = p2[2];
	jacobian[row][col2]     = p1[0];
	jacobian[row][col2 + 1] = p1[1];
	jacobian[row][col2 + 2] = p1[2];
	*/

	Vec3d p  = m_particle1->pos - m_particle2->pos;
	jacobian[row + 1][col1]     =  2*p[0];
	jacobian[row + 1][col1 + 1] =  2*p[1];
	jacobian[row + 1][col1 + 2] =  2*p[2];
	jacobian[row + 1][col2]     = -2*p[0];
	jacobian[row + 1][col2 + 1] = -2*p[1];
	jacobian[row + 1][col2 + 2] = -2*p[2];
}


inline Vec3d derivGradient(const Vec3d& p, const Vec3d& v) {
	double x = p[0];
	double y = p[1];
	double z = p[2];
	double a = v[0];
	double b = v[1];
	double c = v[2];

	Vec3d res;
	res[0] = -3*a*x*(y*y + z*z) - b*y*(-2*x*x + y*y + z*z) - c*z*(-2*x*x + y*y + z*z);
	res[1] = -3*b*y*(x*x + z*z) - a*x*(x*x + -2*y*y + z*z) - c*z*(x*x + -2*y*y + z*z);
	res[2] = -3*c*z*(x*x + y*y) - a*x*(x*x + y*y + -2*z*z) - b*y*(x*x + y*y + -2*z*z);
	res = res/(sqrlen(p)*sqrlen(p)*len(p));
	return res;
}


void RigidJointConstraint::computeGradientDerivative(Matd& jacobianDeriv, int row) {
	int col1 = 3*m_particle1->id;
	int col2 = 3*m_particle2->id;

	Vec3d p1 = m_particle1->pos - m_center;
	Vec3d p2 = m_particle2->pos - m_center;
	double len1 = len(p1);
	double len2 = len(p2);
	Vec3d v1 = m_particle1->vel;
	Vec3d v2 = m_particle2->vel;	
	Vec3d der1 = derivNormVector(p1, m_particle1->vel);
	Vec3d der2 = derivNormVector(p2, m_particle2->vel);
	Vec3d aux1 = derivGradient(p1, v1);
	Vec3d aux2 = derivGradient(p2, v2);

	jacobianDeriv[row][col1]     = aux1[0]*p2[0]/len2 + der2[0]/len1;
	jacobianDeriv[row][col1 + 1] = aux1[1]*p2[1]/len2 + der2[1]/len1;
	jacobianDeriv[row][col1 + 2] = aux1[2]*p2[2]/len2 + der2[2]/len1;
	jacobianDeriv[row][col2]     = aux2[0]*p1[0]/len1 + der1[0]/len2;
	jacobianDeriv[row][col2 + 1] = aux2[1]*p1[1]/len1 + der1[1]/len2;
	jacobianDeriv[row][col2 + 2] = aux2[2]*p1[2]/len1 + der1[2]/len2;

	/*
	jacobianDeriv[row][col1]     = v2[0];
	jacobianDeriv[row][col1 + 1] = v2[1];
	jacobianDeriv[row][col1 + 2] = v2[2];
	jacobianDeriv[row][col2]     = v1[0];
	jacobianDeriv[row][col2 + 1] = v1[1];
	jacobianDeriv[row][col2 + 2] = v1[2];
	*/

	Vec3d p = v1 - v2;
	jacobianDeriv[row + 1][col1]     =  2*p[0];
	jacobianDeriv[row + 1][col1 + 1] =  2*p[1];
	jacobianDeriv[row + 1][col1 + 2] =  2*p[2];
	jacobianDeriv[row + 1][col2]     = -2*p[0];
	jacobianDeriv[row + 1][col2 + 1] = -2*p[1];
	jacobianDeriv[row + 1][col2 + 2] = -2*p[2];
}
