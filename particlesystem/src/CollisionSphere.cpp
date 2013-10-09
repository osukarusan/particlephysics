#include "CollisionSphere.h"

CollisionSphere::CollisionSphere(void)
{
	m_position = Vec3d(0.0, 0.0, 0.0);
	m_radius   = 1.0;
	m_inner    = false;
}

CollisionSphere::~CollisionSphere(void)
{
}

void CollisionSphere::getBoundingBox(Vec3d& min, Vec3d& max) {
	min = m_position - m_radius*Vec3d(1,1,1);
	max = m_position + m_radius*Vec3d(1,1,1);
}

bool CollisionSphere::testCollision(const Particle *p, double eps, Vec3d& pos, Vec3d& nor) 
{
	bool   collision = false;
	Vec3d  toCenter = m_position - p->pos;
	double dist = len(toCenter);
	
	if (m_inner) {
		collision = (m_radius - dist < eps);
	}
	else {
		collision = (dist - m_radius < eps);
	}

	if (collision) {
		Vec3d  v = p->pos - p->prevPos;
		double a = dot(v, v);
		double b = 2*dot(v, p->prevPos - m_position);
		double c = dot(m_position, m_position) + dot(p->prevPos, p->prevPos) 
				   - 2*dot(p->prevPos, m_position) - m_radius*m_radius;
		double det2 = b*b - 4*a*c;
		double lambda = 0;
		if (det2 >= 0) {
			double det = std::sqrt(det2);
			double lambda1 = (-b + det)/(2*a);
			double lambda2 = (-b - det)/(2*a);
			if (lambda1 > 0 && lambda2 > 0) lambda = std::min(lambda1, lambda2);
			else if (lambda1 > 0)			lambda = lambda1;
			else if (lambda2 > 0)			lambda = lambda2;
		}

		pos = p->prevPos + lambda*v;
		nor = pos - m_position;
		normalise(nor);
		if (m_inner) nor *= -1;
	}

	return collision;
}
