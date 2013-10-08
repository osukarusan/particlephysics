#ifndef _CONSTRAINED_PARTICLE_SYSTEM_
#define _CONSTRAINED_PARTICLE_SYSTEM_

#include "ParticleSystem.h"
#include "Constraint.h"
#include "defines.h"

class ConstrainedParticleSystem : public ParticleSystem
{
public:
	ConstrainedParticleSystem(void);
	~ConstrainedParticleSystem(void);

	//virtual int  getDimension()  const;
	//virtual Vecd getState()      const;
	virtual Vecd getDerivative() const;
	//virtual void setState(const Vecd& state);

	Constraint* getConstraint(unsigned int i) const;
	std::vector<Constraint*> getConstraints() const;
	int  getNumConstraints() const;
	int  getConstraintsDimension() const;
	void addConstraint(Constraint* c);
	void clearconstraints();

protected:

	void applyConstraintForces() const;

	std::vector<Constraint*>	m_constraints;
	unsigned int m_totalConstraints;

};


inline Constraint* ConstrainedParticleSystem::getConstraint(unsigned int i) const {
	if (i < m_constraints.size()) return m_constraints[i];
	return NULL;
}

inline std::vector<Constraint*> ConstrainedParticleSystem::getConstraints() const {
	return m_constraints;
}

inline int ConstrainedParticleSystem::getNumConstraints() const {
	return m_constraints.size();
}

inline int ConstrainedParticleSystem::getConstraintsDimension() const {
	return m_totalConstraints;
}

inline void ConstrainedParticleSystem::addConstraint(Constraint *c) {
	m_constraints.push_back(c);
	m_totalConstraints += c->getDimension();
}

inline void ConstrainedParticleSystem::clearconstraints() {
	m_constraints.clear();
	m_totalConstraints = 0;
}
 

#endif