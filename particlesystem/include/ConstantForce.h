#ifndef _GRAVITY_FORCE_
#define _GRAVITY_FORCE_

#include "Force.h"
#include "defines.h"

class ConstantForce : public Force
{

public:
	ConstantForce(void);
	virtual ~ConstantForce(void);

	virtual void apply();

	void  setGravityConstant(const Vec3d& g);
	Vec3d getGravityConstant() const;

private:

	Vec3d G;

};


inline void ConstantForce::setGravityConstant(const Vec3d& g) {
	G = g;
}

inline Vec3d ConstantForce::getGravityConstant() const {
	return G;
}



#endif