#ifndef _RIGID_JOINT_CONSTRAINT_
#define _RIGID_JOINT_CONSTRAINT_

#include "Constraint.h"
#include "Particle.h"

class RigidJointConstraint : public Constraint
{
public:
	RigidJointConstraint(void);
	~RigidJointConstraint(void);
	
	virtual unsigned int getDimension() const;
	virtual Vecd getConstraint();
	virtual Vecd getDerivative();
	virtual void computeGradient(Matd& jacobian, int row);
	virtual void computeGradientDerivative(Matd& jacobianDeriv, int row);

	void setParticles(Particle* p1, Particle* p2, const Vec3d& center);

protected:

	Particle* m_particle1;
	Particle* m_particle2;
	Vec3d	  m_center;
	double	  m_product;
	double	  m_distance;

};


inline unsigned int RigidJointConstraint::getDimension() const {
	return 2;
}

inline void RigidJointConstraint::setParticles(Particle* p1, Particle* p2, const Vec3d& c) {
	m_particle1 = p1;
	m_particle2 = p2;
	m_center    = c;
	Vec3d vec1 = p1->pos - c;
	Vec3d vec2 = p2->pos - c;
	vec1.Normalise();
	vec2.Normalise();
	m_product = dot(vec1, vec2);
	//m_product   = dot(p1->pos - c, p2->pos - c);
	m_distance  = len(p1->pos - p2->pos);
}


#endif