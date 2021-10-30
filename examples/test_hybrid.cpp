
#include "experiment.h"

const double g = 9.81;
const double amortissement = 0.9;
const double gardsTol = 0.01;

/* ODE definitions */
vector<T<interval>> BouncingBall(vector<T<interval>> x){
	vector<T<interval>> f = vector<T<interval>>(DIM);
	f[0] = x[1];
	f[1] = interval(-g);
	return f;
}

/* Modifications definitions */
v_interval Bump(v_interval x){
	v_interval new_x = v_interval(DIM);
	new_x[0] = x[0];
	new_x[1] = -interval(amortissement)*x[1];
	return new_x;
}
	

/* Main function */
int main()
{
	/* Initialise external variables: */
	DIM = 2;
	STATES = 1;
	
	/* Construct System of ODE: */
	vector<ODE> system;
	ODE ode((functionODE)BouncingBall);
	system.push_back(ode);

	/* Construct inGards: */
	vector<v_interval> inGards;
	v_interval x_pos(DIM);
	x_pos[0] = interval(0., entire().sup());
	x_pos[1] = entire(); 
	inGards.push_back(x_pos);

	/* Construct outGards: */
	vector<vector<v_interval>> outGards;
	vector<v_interval> one_gards;
	v_interval x_zero(DIM);
	x_zero[0] = interval(0.);
	x_zero[1] = entire(); 
	one_gards.push_back(x_zero);
	outGards.push_back(one_gards);

	/* Construct outMod: */
	vector<vector<functionMod>> outMod;
	vector<functionMod> one_mod(1, (functionMod)Bump);
	outMod.push_back(one_mod);

	/* Set initial interval: */
	v_interval x0(DIM);	
	x0[0] = interval(1., 1.1);
	x0[1] = interval(0., 0.);

	/* Set initial hybrid state: */
	vector<State> enclosure;
	State init_state = State(0, x0);
	enclosure.push_back(init_state);

	/* Construct Hybrid: */
	Hybrid hybrid = Hybrid(system, inGards, outGards, outMod, enclosure);

	/* Set experience parameters: */
	Experiment exp = Experiment(hybrid, x0, 10, 0.001, 0.5, 0., 1.0, 0.00001);

	/* Run solving program: */
	exp.solveHybrid();

	return 0;
}