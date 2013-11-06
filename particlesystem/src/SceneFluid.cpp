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

	int numParticles = DataManager::mFluidParticles;
	for (int i = 0; i < numParticles; i++) {
		Particle *p = new Particle();

		double rrad =   0.25*double(rand()%1024)/1024.0;
		double rang = 2*M_PI*double(rand()%1024)/1024.0;
		double rver =    0.8*double(rand()%1024)/1024.0;
		p->pos   = p->prevPos = Vec3d(rrad*cos(rang), 3.0 + rver, rrad*sin(rang));
		p->vel   = p->vel     = Vec3d(0,0,0);
		p->color = Vec3f(0.2f, 1.0f, 1.0f);
		p->mass  = 0.01;

		particles.push_back(p);
	}
	
	boxContainer = new CollisionAABB();
	boxContainer->setPosition(Vec3d(-1.0, 0.0, -1.0));
	boxContainer->setSize(Vec3d(2.0, 4.0, 2.0));
	boxContainer->useInnerSide(true);

	std::vector<Particle> vparts;
	for (int i = 0; i < numParticles; i++) {
		vparts.push_back(*particles[i]);
	}
	DataManager::mParticles.push_back(vparts);
}

void SceneFluid::update() {

	int    numParticles = particles.size();
	double hTime        = DataManager::mTimeStep;
	double hRadius		= DataManager::mFluidNeighborRadius;
	double fluidDensity = DataManager::mFluidDensity;
	double c_sound      = DataManager::mCsound;

	// find particle neighbors
	std::vector<std::vector<int> > neighbors(numParticles);
	findNeighbors(neighbors, hRadius);

	// calculate density for each particle
	for (int i = 0; i < numParticles; i++) {
		Particle* pi = particles[i];
		double density = pi->mass * W(Vec3d(0,0,0), hRadius);
		for (int j = 0; j < neighbors[i].size(); j++) {
			Particle *pj = particles[neighbors[i][j]];
			density += pj->mass * W(pj->pos - pi->pos, hRadius);
		}
		pi->density = density;
	}

	// calculate pressure for each particle
	std::vector<double> pressure(numParticles);
	for (int i = 0; i < numParticles; i++) {
		pressure[i] = c_sound * c_sound * (particles[i]->density - fluidDensity);
	}

	// calculate acceleration for each particle
	std::vector<Vec3d> acceleration(numParticles);
	for (int i = 0; i < numParticles; i++) {

		Particle* pi = particles[i];

		// pressure term
		Vec3d a_p = Vec3d(0, 0, 0);
		double ip = pressure[i]/(pi->density*pi->density);
		for (int ni = 0; ni < neighbors[i].size(); ni++) {
			int j = neighbors[i][ni];
			Particle* pj = particles[j];
			double Pij = -pj->mass*(ip + pressure[j]/(pj->density*pj->density));
			a_p += Pij*dWdx(pj->pos - pi->pos, hRadius);
		}

		// viscosity term
		Vec3d a_v = Vec3d(0, 0, 0);
		double mu = DataManager::mFluidDynamicViscosity;
		for (int ni = 0; ni < neighbors[i].size(); ni++) {
			int j = neighbors[i][ni];
			Particle* pj = particles[i];
			Vec3d Vij = mu*pj->mass*(pj->vel - pi->vel)/(pi->density*pj->density);
			a_v += Vij*lapW(pj->pos - pi->pos, hRadius);
		}

		// gravity term
		Vec3d a_g = Vec3d(0, -DataManager::mGravityValue, 0);

		// sum
		acceleration[i] = a_p + a_v + a_g;
	}

	// integration step (Euler)
	for (int i = 0; i < numParticles; i++) {
		particles[i]->prevVel = particles[i]->vel;
		particles[i]->vel     = acceleration[i]*hTime;
		particles[i]->prevPos = particles[i]->pos;
		particles[i]->pos     = particles[i]->vel*hTime;
	}

	// collision with the container
	double kr  = DataManager::mCoeffRestitution;
	double kt  = DataManager::mTangentialFriction;
	double eps = DataManager::mCollisionEpsilon;
	Vec3d pos, nor;
	for (int i = 0; i < numParticles; i++) {
		Particle *p = particles[i];
		if (boxContainer && boxContainer->testCollision(p, eps, pos, nor)) {
			Vec3d velN = dot(nor, p->vel)*nor;
			Vec3d velT = p->vel - velN;
			p->vel = kt*velT - kr*velN;
			p->pos = p->pos - (1 + kr)*(dot(nor, p->pos) - dot(nor, pos))*nor + eps*nor;
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
	double q = len(x)/h;
	double s = 8.0/(M_PI*h*h*h);
	if (q < 0.5)	return s*(6*q*q*q - 6*q*q + 1);
	else if (q < 1) return s*(2*(1 - q)*(1 - q)*(1 - q));
	else			return 0;
}

Vec3d SceneFluid::dWdx(const Vec3d& x, double h) {
	double q = len(x)/h;
	double s = 6.0*8.0/(M_PI*h*h*h*h);
	Vec3d  d = norm(x);
	if (q < 0.5)	return s*(3*q*q - 2*q)*d;
	else if (q < 1) return s*(-(1 - q)*(1 - q))*d;
	else			return 0*d;
}

double SceneFluid::lapW(const Vec3d& x, double h) {
	double q = len(x)/h;
	double s = 6.0*8.0/(M_PI*h*h*h);
	if (q < 0.5)	return s*(6*q - 2);
	else if (q < 1) return s*(2*(1 - q));
	else			return 0;
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