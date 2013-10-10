#include "MassSpringForce.h"

MassSpringForce::MassSpringForce(void)
{
	m_kd = 1.0;
	m_ks = 0.0;
	m_p1 = m_p2 = NULL;
	m_L  = 0;
}

MassSpringForce::~MassSpringForce(void)
{
}

void MassSpringForce::apply() {
	
	Vec3d  dir  = m_p2->pos - m_p1->pos;
	double dist = len(dir);
	normalise(dir);

	double spring  = m_ks*(dist - m_L);
	double damping = m_kd*dot(m_p2->vel - m_p1->vel, m_p2->pos - m_p1->pos)/dist;
	Vec3d  sforce  = (spring + damping)*dir; 

	m_p1->force += sforce;
	m_p2->force -= sforce;

}