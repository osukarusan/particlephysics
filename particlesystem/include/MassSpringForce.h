#ifndef _MASS_SPRING_FORCE_
#define _MASS_SPRING_FORCE_

#include "Force.h"

class MassSpringForce : public Force
{

public:
	MassSpringForce(void);
	virtual ~MassSpringForce(void);

	virtual void apply();

	void setParticlePair(Particle* p1, Particle* p2);

	void setSpringCoefficient(double ks);
	void setDampingCoefficient(double kd);
	void setRestingLength(double L);
	
	double getSpringCoefficient()  const;
	double getDampingCoefficient() const;
	double getRestingLength()	   const;

	void correctPosition();

private:

	Particle *m_p1;
	Particle *m_p2;
	double m_ks, m_kd, m_L;

};



inline void MassSpringForce::setParticlePair(Particle* p1, Particle* p2) {
	m_p1 = p1;
	m_p2 = p2;
}

inline void MassSpringForce::setRestingLength(double L) {
	m_L = L;
}

inline void MassSpringForce::setSpringCoefficient(double ks) {
	m_ks = ks;
}

inline void MassSpringForce::setDampingCoefficient(double kd) {
	m_kd = kd;
}

inline double MassSpringForce::getSpringCoefficient() const {
	return m_ks;
}

inline double MassSpringForce::getDampingCoefficient() const {
	return m_kd;
}

inline double MassSpringForce::getRestingLength() const {
	return m_L;
}

#endif