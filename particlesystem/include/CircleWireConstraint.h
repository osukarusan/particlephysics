#ifndef _CIRCLE_WIRE_CONSTRAINT_
#define _CIRCLE_WIRE_CONSTRAINT_

#include "Constraint.h"
#include "Particle.h"
#include "defines.h"

class CircleWireConstraint : public Constraint
{
public:
	CircleWireConstraint(void);
	~CircleWireConstraint(void);

	virtual unsigned int getDimension() const;
	virtual Vecd getConstraint();
	virtual Vecd getDerivative();
	virtual void computeGradient(Matd& jacobian, int row);
	virtual void computeGradientDerivative(Matd& jacobianDeriv, int row);

	Vec3d     getCenter()   const;
	double    getRadius()   const;
	Particle* getParticle() const;
	void setCenter(const Vec3d& c);
	void setRadius(double r);
	void setParticle(Particle* p);

private:

	Vec3d  m_center;
	double m_radius;

	Particle* m_particle;

};

inline unsigned int CircleWireConstraint::getDimension() const {
	return 1;
}

inline Vec3d CircleWireConstraint::getCenter() const {
	return m_center;
}

inline double CircleWireConstraint::getRadius() const {
	return m_radius;
}

inline Particle* CircleWireConstraint::getParticle() const {
	return m_particle;
}

inline void CircleWireConstraint::setCenter(const Vec3d &c) {
	m_center = c;
}

inline void CircleWireConstraint::setRadius(double r) {
	m_radius = r;
}

inline void CircleWireConstraint::setParticle(Particle* p) {
	m_particle = p;
}

#endif