#ifndef _FIXED_DISTANCE_CONSTRAINT_
#define _FIXED_DISTANCE_CONSTRAINT_

#include "Constraint.h"
#include "Particle.h"

class FixedDistanceConstraint : public Constraint
{
public:
	FixedDistanceConstraint(void);
	~FixedDistanceConstraint(void);

	virtual unsigned int getDimension() const;
	virtual Vecd getConstraint();
	virtual Vecd getDerivative();
	virtual void computeGradient(Matd& jacobian, int row);
	virtual void computeGradientDerivative(Matd& jacobianDeriv, int row);

	void setParticles(Particle* p1, Particle* p2);
	void setDistance(double d);
	double getDistance() const;

protected:

	Particle* m_particle1;
	Particle* m_particle2;
	double    m_distance;

};


inline unsigned int FixedDistanceConstraint::getDimension() const {
	return 1;
}

inline void FixedDistanceConstraint::setParticles(Particle* p1, Particle* p2) {
	m_particle1 = p1;
	m_particle2 = p2;
}

inline void FixedDistanceConstraint::setDistance(double d) {
	m_distance = d;
}

inline double FixedDistanceConstraint::getDistance() const {
	return m_distance;
}

#endif