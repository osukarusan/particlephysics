#ifndef _COLLISION_PLANE_
#define _COLLISION_PLANE_

#include "CollisionTest.h"
#include "defines.h"

class CollisionPlane : public CollisionTest
{
public:
	CollisionPlane(void);
	~CollisionPlane(void);

	virtual void getBoundingBox(Vec3d& min, Vec3d& max);
	virtual bool testCollision(const Particle* particle, double eps, Vec3d& pos, Vec3d& nor);

	Vec3d	getNormal() const;
	double	getK()		const;

	void	setNormal(const Vec3d& n);
	void    setK	 (double k);
	void	setPlane (const Vec3d& n, double k);

	virtual void move(const Vec3d& v);	

private:

	Vec3d	m_normal;
	double	m_k;

};

inline Vec3d CollisionPlane::getNormal() const {
	return m_normal;
}

inline double CollisionPlane::getK() const {
	return m_k;
}

inline void CollisionPlane::setNormal(const Vec3d& n) {
	m_normal = n;
}

inline void CollisionPlane::setK(double k) {
	m_k = k;
}

inline void CollisionPlane::setPlane(const Vec3d& n, double k) {
	m_normal = n;
	m_k = k;
}

#endif