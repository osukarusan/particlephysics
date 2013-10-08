#include "ConstrainedParticleSystem.h"

ConstrainedParticleSystem::ConstrainedParticleSystem(void)
{
	m_totalConstraints = 0;
}

ConstrainedParticleSystem::~ConstrainedParticleSystem(void)
{
	for (int i = 0; i < m_constraints.size(); i++)
		delete m_constraints[i];
}


Vecd ConstrainedParticleSystem::getDerivative() const {

	// clear force accumulators
	for (int i = 0; i < m_particles.size(); i++) {
		m_particles[i]->force = Vec3d(0.0, 0.0, 0.0);
	}

	// apply forces
	for (int i = 0; i < m_forces.size(); i++) {
		m_forces[i]->apply();
	}

	// compute and apply constraint forces
	applyConstraintForces();

	// compute derivatives
	Vecd deriv(this->getDimension());
	for (int i = 0; i < m_particles.size(); i++) {
		deriv[6*i    ] = m_particles[i]->vel[0];
		deriv[6*i + 1] = m_particles[i]->vel[1];
		deriv[6*i + 2] = m_particles[i]->vel[2];
		deriv[6*i + 3] = m_particles[i]->force[0]/m_particles[i]->mass;
		deriv[6*i + 4] = m_particles[i]->force[1]/m_particles[i]->mass;
		deriv[6*i + 5] = m_particles[i]->force[2]/m_particles[i]->mass;
	}
	
	return deriv;

}

void ConstrainedParticleSystem::applyConstraintForces() const {

	const double ks = 1.0;
	const double kd = 1.0;

	int n = m_particles.size();
	int m = m_totalConstraints;	
	Vecd qd(3*n);				// velocities vector
	Vecd Q (3*n);				// forces vector
	Matd W (3*n, 3*n);			// inverse mass matrix
	Vecd C (m);					// constraints vector
	Vecd Cd(m);					// constraints time derivative vector
	Matd J (m, 3*n);			// Jacobian
	Matd Jd(m, 3*n);			// Jacobian time derivative
	Vecd L (m);					// Lagrangian multipliers
	for (int i = 0; i < 3*n; i++)
		for (int j = 0; j < 3*n; j++)
			W[i][j] = 0.0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < 3*n; j++)
			J[i][j] = Jd[i][j] = 0.0;

	// build matrices
	for (int i = 0; i < n; i++) {
		Particle* par = m_particles[i];
		qd[3*i  ] = par->vel[0];
		qd[3*i+1] = par->vel[1];
		qd[3*i+2] = par->vel[2];
		Q [3*i  ] = par->force[0];
		Q [3*i+1] = par->force[1];
		Q [3*i+2] = par->force[2];
		W [3*i][3*i] = W[3*i+1][3*i+1] = W[3*i+2][3*i+2] = 1.0/par->mass; 
	}

	int row = 0;
	for (int i = 0; i < m_constraints.size(); i++) {
		Constraint* con = m_constraints[i];
		Vecd vcon = con->getConstraint();
		Vecd dcon = con->getDerivative();

		for (int j = 0; j < con->getDimension(); j++) {
			C [row + j] = vcon[j];
			Cd[row + j] = dcon[j];
		}
		con->computeGradient(J, row);
		con->computeGradientDerivative(Jd, row);
		row += con->getDimension();
	}

	// solve system for L: (J*W*J^T)*L = -Jd*qd - J*W*Q 
	// J*W*J^T is positive definite and symmetric
	Matd Jt = trans(J);
	Matd A = J*W*Jt;
	Vecd B = -Jd*qd - J*W*Q - ks*C - kd*Cd;
	L = inv(A)*B;
	Vecd ConstraintForce = Jt*L;

	//apply forces
	for (int i = 0; i < n; i++) {
		Particle* p = m_particles[i];
		p->force[0] += ConstraintForce[3*i  ];
		p->force[1] += ConstraintForce[3*i+1];
		p->force[2] += ConstraintForce[3*i+2];
	}

}