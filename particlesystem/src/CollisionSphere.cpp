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
		if (m_radius - dist < eps) {
			collision = true;
			nor = toCenter/dist;
			pos = m_position - m_radius*nor;
		}
	}
	else {
		if (dist - m_radius < eps) {
			collision = true;
			nor = -toCenter/dist;
			pos = m_position + m_radius*nor;
		}
	}

	return collision;
}
