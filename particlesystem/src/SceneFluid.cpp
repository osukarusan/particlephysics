#include "SceneFluid.h"
#include "DataManager.h"
#include <vector>
#include <map>
#define M_PI 3.14159265358979323846


SceneFluid::SceneFluid(void)
{
	boxContainer = NULL;
}


SceneFluid::~SceneFluid(void)
{
	for (int i = 0; i < int(particles.size()); i++) {
		delete particles[i];
	}
	particles.clear();
}


void SceneFluid::init() {

	for (int i = 0; i < int(particles.size()); i++) {
		delete particles[i];
	}
	particles.clear();

	int numParticles;
	if (DataManager::mFluid3D) {
		numParticles = 1000;
		for (int i = 0; i < numParticles; i++) {
			Particle *p = new Particle();
			double x = -0.5 + 0.1*double(i%10);
			double z = -0.5 + 0.1*double((i/10)%10);
			double y =  2.5 + 0.1*double(i/100);
			p->pos   = p->prevPos = Vec3d(x, y, z);
			p->vel   = p->vel     = Vec3d(0,0,0);
			p->color = Vec3f(0.2f, 1.0f, 1.0f);
			p->mass  = 1.0;
			particles.push_back(p);
		}
	
		boxContainer = new CollisionAABB();
		boxContainer->setPosition(Vec3d(-1.0, 0.0, -1.0));
		boxContainer->setSize(Vec3d(2.0, 8.0, 2.0));
		boxContainer->useInnerSide(true);
	}
	else {
		numParticles = 900;
		for (int i = 0; i < numParticles; i++) {
			Particle *p = new Particle();
			double x = -1.5 + 0.1*double(i%30);
			double z =  0;
			double y =  1.5 + 0.1*double(i/30);
			p->pos   = p->prevPos = Vec3d(x, y, z);
			p->vel   = p->vel     = Vec3d(0,0,0);
			p->color = Vec3f(0.2f, 1.0f, 1.0f);
			p->mass  = 1.0;
			particles.push_back(p);
		}
	
		boxContainer = new CollisionAABB();
		boxContainer->setPosition(Vec3d(-3.0, 0.0, -1.0));
		boxContainer->setSize(Vec3d(6.0, 8.0, 2.0));
		boxContainer->useInnerSide(true);
	}

	std::vector<Particle> vparts;
	for (int i = 0; i < numParticles; i++) {
		vparts.push_back(*particles[i]);
	}
	DataManager::mParticles.push_back(vparts);
}

void SceneFluid::update() {

	int    numParticles		   = particles.size();
	double Dt				   = DataManager::mTimeStep;
	double hRadius			   = 0.3;
	Vec3d  a_g				   = Vec3d(0, -DataManager::mGravityValue, 0);
	double kPressure		   = 0.08;
	double kPressureNear	   = 0.10;
	double restDensity         = DataManager::mFluidRestDensity;
	double kSurfaceTension     = DataManager::mFluidSurfaceTension;
	double kLinearViscosity    = DataManager::mFluidLinearViscosity;
	double kQuadraticViscosity = DataManager::mFluidQuadraticViscosity;

	int numSteps = 1;
	for (int nstep = 0; nstep < numSteps; nstep++) {

		// move particles
		for (int i = 0; i < numParticles; i++) {
			particles[i]->vel += a_g*Dt;
			particles[i]->prevPos = particles[i]->pos;
			particles[i]->pos += particles[i]->vel*Dt; 
		}

		// find particle neighbors
		std::vector<std::vector<int> > neighbors(numParticles);
		findNeighbors(neighbors, hRadius);

		// calculate density for each particle
		std::vector<double> nearDensity(numParticles, 0.0);
		for (int i = 0; i < numParticles; i++) {
			Particle* pi = particles[i];
			double density  = 0;
			double ndensity = 0;
			for (int j = 0; j < neighbors[i].size(); j++) {
				Particle *pj = particles[neighbors[i][j]];
				density  += pj->mass * W(pj->pos - pi->pos, hRadius);
				ndensity += pj->mass * Wnear(pj->pos - pi->pos, hRadius);
			}
			pi->density = density;
			nearDensity[i] = ndensity;
		}

		// calculate pressure
		std::vector<double> P(numParticles, 0.0);
		std::vector<double> Pnear(numParticles, 0.0);
		for (int i = 0; i < numParticles; i++) {
			P[i] = kPressure*(particles[i]->density - restDensity);
			Pnear[i] = kPressureNear*nearDensity[i];
		}

		// calculate relaxed positions
		for (int i = 0; i < numParticles; i++) {
			
			Particle* pi = particles[i];
			Vec3d pos = pi->pos;

			for (int j = 0; j < neighbors[i].size(); j++) {

				int idj = neighbors[i][j];
				Particle *pj = particles[idj];
				Vec3d dx = pj->pos - pi->pos;
				double r = len(dx);

				// pressure
				Vec3d Dp = Dt*Dt * ((Pnear[i] + Pnear[idj])*dWdxnear(dx, hRadius)/4 + (P[i] + P[idj])*dWdx(dx, hRadius)/3)/2;
				pos -= Dp/pi->mass;

				// surface tension
				Vec3d Ds = r*kSurfaceTension/pi->mass * pj->mass*dWdx(dx, hRadius)/3.0;
				pos += Ds;

				// viscosity
				if (r < hRadius) {
					Vec3d dir = dx/r;
					double u = dot(pj->vel - pi->vel, dir);
					if (u > 0) {
						Vec3d I = 0.5*Dt*(1.0 - r/hRadius)*(kLinearViscosity*u + kQuadraticViscosity*u*u)*dir;
						pos -= Dt*I;
					}
				}
			}

			pi->pos = pos;
			pi->vel = (pi->pos - pi->prevPos)/Dt;
		}

		// collision with the container
		double kr  = 0.1;
		double kt  = 0.1;
		double eps = 0.05;
		Vec3d pos, nor;
		for (int i = 0; i < numParticles; i++) {
			Particle *p = particles[i];
			if (boxContainer && boxContainer->testCollision(p, eps, pos, nor)) {
				Vec3d velN = dot(nor, p->vel)*nor;
				Vec3d velT = p->vel - velN;
				p->vel = kt*velT - kr*velN;
				p->pos = pos + eps*nor;
			}
		}
	}


	// update data manager (needed for replay)
	std::vector<Particle> vparts;
	for (int i = 0; i < numParticles; i++) {
		vparts.push_back(*particles[i]);
	}
	DataManager::mParticles.push_back(vparts);
}


double SceneFluid::W(const Vec3d& x, double h) {
	double q = std::max(1.0 - len(x)/h, 0.0);
	return 20.0/(2*M_PI*h*h)*q*q*q;
}

double SceneFluid::Wnear(const Vec3d& x, double h) {
	double q = std::max(1.0 - len(x)/h, 0.0);
	return 30.0/(2*M_PI*h*h)*q*q*q*q;
}

Vec3d SceneFluid::dWdx(const Vec3d& x, double h) {
	double q = std::max(1.0 - len(x)/h, 0.0);
	return 3*20.0/(2*M_PI*h*h)*q*q*norm(x);
}

Vec3d SceneFluid::dWdxnear(const Vec3d& x, double h) {
	double q = std::max(1.0 - len(x)/h, 0.0);
	return 4*30.0/(2*M_PI*h*h)*q*q*q*norm(x);
}

double SceneFluid::lapW(const Vec3d& x, double h) {
	double q = std::max(1.0 - len(x)/h, 0.0);
	return 6*20.0/(2*M_PI*h*h)*q;
}

double SceneFluid::lapWnear(const Vec3d& x, double h) {
	double q = std::max(1.0 - len(x)/h, 0.0);
	return 12*30.0/(2*M_PI*h*h)*q*q;
}

void SceneFluid::findNeighbors(std::vector<std::vector<int> >& neighbors, double hLength) {

	Vec3d s = boxContainer->getSize()/hLength;
	Vec3d bmin = boxContainer->getPosition();

	int dim[3];
	dim[0] = int(s[0] + 0.95);
	dim[1] = int(s[1] + 0.95);
	dim[2] = int(s[2] + 0.95);
	int nc = dim[0]*dim[1]*dim[2];
	int dx = dim[1]*dim[2];
	int dy = dim[2];
	int dz = 1;

	std::map<int, std::vector<int> > grid;
	for (int i = 0; i < int(particles.size()); i++) {
		Vec3d coords = (particles[i]->pos - bmin)/hLength;
		int x = int(coords[0]);
		int y = int(coords[1]);
		int z = int(coords[2]);
		grid[x*dx + y*dy + z*dz].push_back(i);
	}

	for (int i = 0; i < particles.size(); i++) {
		Particle* p = particles[i];
		Vec3d coords = (p->pos - bmin)/hLength;
		int x = int(coords[0]);
		int y = int(coords[1]);
		int z = int(coords[2]);
		for (int ix = -1; ix <= 1; ix++) {
			for (int iy = -1; iy <= 1; iy++) {
				for (int iz = -1; iz <= 1; iz++) {
					int gid = (x + ix)*dx + (y + iy)*dy + (z + iz)*dz;
					if (gid >= 0 && gid < nc) {
						std::vector<int>& neighs = grid[gid];
						for (int j = 0; j < neighs.size(); j++) {
							if (neighs[j] != i && len(p->pos - particles[neighs[j]]->pos) < hLength)
								neighbors[i].push_back(neighs[j]);
						}
					}
				}
			}
		}
	}

}