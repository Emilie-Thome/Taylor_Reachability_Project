
#include "experiment.h"

/* ODE definitions */
vector<T<interval>> Brusselator(vector<T<interval>> x){
	vector<T<interval>> f = vector<T<interval>>(DIM);
	f[0] = interval(1.) + x[0]*x[0]*x[1] - 2.5*x[0];
	f[1] = 1.5*x[0] - x[0]*x[0]*x[1];
	return f;
}
vector<T<interval>> Linear(vector<T<interval>> x){
	vector<T<interval>> f = vector<T<interval>>(DIM);
	f[0] = 1;
	return f;
}
vector<T<interval>> Exponential(vector<T<interval>> x){
	vector<T<interval>> f = vector<T<interval>>(DIM);
	f[0] = -x[0];
	return f;
}
vector<T<interval>> Cos(vector<T<interval>> x){
	vector<T<interval>> f = vector<T<interval>>(DIM);
	f[0] = x[1];
	f[1] = -pow(interval(2)*pi(),2)*x[0];
	return f;
}
	

/* Main function */
int main()
{
	/* Initialise external variables: */
	DIM = 1;

	/* Construct ODE: */
	ODE ode((functionODE)Linear);

	/* Set initial interval: */
	v_interval x0(DIM);	
	x0[0] = interval(0.9999, 1.0001);
	// x0[1] = interval(0., 0.0001);
	
	/* Set experience parameters: */
	Experiment exp = Experiment(ode, x0, 10, 0.001, 0.5, 0., 1000, 0.00001);

	/* Run solving program: */
	exp.solveODE();

	return 0;
}