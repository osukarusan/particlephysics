#ifndef _SCENE_FLUID_
#define _SCENE_FLUID_

#include "CollisionAABB.h"
#include <vector>

class SceneFluid
{
public:
	SceneFluid(void);
	~SceneFluid(void);

	void init();
	void update();

private:

	void findNeighbors(std::vector<std::vector<int> >& n, double hLength);

	double    W(const Vec3d& x, double h);
	Vec3d  dWdx(const Vec3d& x, double h);
	double lapW(const Vec3d& x, double h);
	
	double    Wnear(const Vec3d& x, double h);
	Vec3d  dWdxnear(const Vec3d& x, double h);
	double lapWnear(const Vec3d& x, double h);

	std::vector<Particle*> particles;
	CollisionAABB*	boxContainer;	   


};

#endif