#include "CollisionPlane.h"


CollisionPlane::CollisionPlane(void)
{
	m_normal = Vec3d(0, 0, 0);
	m_k = 0;
}


CollisionPlane::~CollisionPlane(void)
{
}

void CollisionPlane::getBoundingBox(Vec3d& min, Vec3d& max) 
{
	min = Vec3d(-PS_INFINITE, -PS_INFINITE, -PS_INFINITE);
	max = Vec3d( PS_INFINITE,  PS_INFINITE,  PS_INFINITE);
}

bool CollisionPlane::testCollision(const Particle* particle, double eps, 
								   Vec3d& pos, Vec3d& nor)
{
	double d = dot(particle->pos, m_normal) + m_k;
	pos = particle->pos;  //TODO!!
	nor = m_normal;
	return d < eps;
}

void CollisionPlane::move(const Vec3d& d) {

}

