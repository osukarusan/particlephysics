#ifndef _PARTICLE_
#define _PARTICLE_

#include "defines.h"

class Particle
{

public:

	static const int Dimension = 6;

	Particle(void);
	Particle(const Vec3d& p, const Vec3d& v, float m); 
	Particle(const Particle& p);
	~Particle(void);

	Vec3d pos;
	Vec3d vel;
	Vec3d force;
	float mass;

	Vec3f color;

	int   id;

};

#endif