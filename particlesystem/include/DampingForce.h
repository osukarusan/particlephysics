#ifndef _DAMPING_FORCE_
#define _DAMPING_FORCE_

#include "Force.h"

class DampingForce : public Force
{
public:
	DampingForce(void);
	virtual ~DampingForce(void);

	virtual void apply();

	void   setDampingCoefficient(double kd);
	double getDampingCoefficient() const;

private:

	double m_kd;

};

inline void DampingForce::setDampingCoefficient(double kd) {
	m_kd = kd;
}

inline double DampingForce::getDampingCoefficient() const {
	return m_kd;
}

#endif