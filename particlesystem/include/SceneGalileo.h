#ifndef _SCENE_GALILEO_
#define _SCENE_GALILEO_

#include "ParticleSystem.h"
#include "EulerIntegrator.h"
#include "RungeKuttaIntegrator.h"
#include "MidpointIntegrator.h"
#include "VerletIntegrator.h"

class SceneGalileo
{

public:

	SceneGalileo(void);
	~SceneGalileo(void);

	void init();
	void update();
	
private:

	ParticleSystem* m_GalileoAnalytic;
	ParticleSystem* m_GalileoEuler;
	ParticleSystem* m_GalileoRungeKutta;

	EulerIntegrator      m_Euler;
	//MidpointIntegrator   m_Midpoint;
	RungeKuttaIntegrator m_RungeKutta;

};

#endif