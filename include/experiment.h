

#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "ode.h"
#include "hybrid.h"
#include "polynome.h"
#include "plot_enclosure.h"

/* standard headers */
#include <iostream>
#include <string>
#include <limits.h>
#include <cfloat>

/* filib include */
#include "filib_interval.h"

/* fadbad include */
#include "fadbad_interval.h"
using namespace fadbad;

/* vector include */
#include <vector>
using namespace std;
typedef vector<interval> v_interval;

/* Experiment class definition */
class Experiment
{
private:
	int        n;
	double     h;
	double     alpha;
	double     t;
	double     t_end;
	double     epsilon;
	v_interval xi = v_interval(DIM);
	ODE        ode;
	Hybrid     hybrid;
	Plot       plot;

public:
	/* Constructors */
	Experiment(ODE ode, v_interval x0, int n, double h, double alpha, double t0, double t_end, double epsilon);
	Experiment(Hybrid hybrid, v_interval x0, int n, double h, double alpha, double t0, double t_end, double epsilon);

	/* Compute a tight enclosure of x'i+1 from x'i for ODE or hybrid systems */
	void nextODE();
	void nextHybrid();

	/* Solve the experiment for ODE and hybrid systems */
	void solveODE();
	void solveHybrid();

	/* Print vector of intervals */
	void print_enclosure();

	/* Compute polynomial enclosure coefficients of x'i+1 from x'i */
	Polynome nextPolynome();

	/* Return true is the vector of interval has an empty interval
	   because then it would mean that the state is not reachable */
	bool isEmpty(v_interval xi);

	/* Return the intersection of the two vector of intervals */
	v_interval intersection(v_interval x1, v_interval x2);

	/* Return the intersection of the two vector of intervals */
	v_interval vector_hull(v_interval x1, v_interval x2);

	/* Return the exclusion the second vector of intervals over first one.
	   If their is an entire interval in the second vector then the exclusion
	   is not done for this interval as it is the "not defined" guard. */
	v_interval exclude(v_interval x1, v_interval x2);

};



#endif