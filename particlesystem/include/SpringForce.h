#ifndef _SPRING_FORCE_
#define _SPRING_FORCE_

#include "Force.h"

class SpringForce : public Force
{

public:
	SpringForce(void);
	~SpringForce(void);

	virtual void apply();

	void setEquilibriumPoint(const Vec3d& eqPoint);
	void setSpringCoefficient(double ks);
	void setDampingCoefficient(double kd);
	
	Vec3d  getEquilibriumPoint()   const;
	double getSpringCoefficient()  const;
	double getDampingCoefficient() const;

private:

	Vec3d  m_equilibrium;
	double m_ks, m_kd;

};


inline void SpringForce::setEquilibriumPoint(const Vec3d& eqPoint) {
	m_equilibrium = eqPoint;
}

inline void SpringForce::setSpringCoefficient(double ks) {
	m_ks = ks;
}

inline void SpringForce::setDampingCoefficient(double kd) {
	m_kd = kd;
}

inline Vec3d SpringForce::getEquilibriumPoint() const {
	return m_equilibrium;
}

inline double SpringForce::getSpringCoefficient() const {
	return m_ks;
}

inline double SpringForce::getDampingCoefficient() const {
	return m_kd;
}

#endif