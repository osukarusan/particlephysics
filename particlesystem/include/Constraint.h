#ifndef _CONSTRAINT_
#define _CONSTRAINT_

#include "defines.h"

class Constraint
{
public:
	Constraint(void);
	~Constraint(void);

	virtual unsigned int getDimension() const = 0;
	virtual Vecd getConstraint() = 0;
	virtual Vecd getDerivative() = 0;
	virtual void computeGradient(Matd& jacobian, int row) = 0;
	virtual void computeGradientDerivative(Matd& jacobianDeriv, int row) = 0;

};


#endif