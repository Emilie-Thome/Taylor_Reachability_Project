

#ifndef ODE_H
#define ODE_H


/* filib include */
#include "filib_interval.h"

/* fadbad include */
#include "fadbad_interval.h"
using namespace fadbad;

/* vector include */
#include <vector>
using namespace std;

/* Definitions */
typedef vector<interval> v_interval;
typedef vector<T<interval>> (* functionODE)(vector<T<interval>> arg);

/* System dimension */
extern int DIM;

/* ODE class */
class ODE
{
private:
	vector<T<interval>> x = vector<T<interval>>(DIM);		// Independent variables
	vector<T<interval>> f = vector<T<interval>>(DIM);		// Dependent variables
	functionODE func;

public:
	/* Constructors */
	ODE(){}
	ODE(functionODE func);

	/* Get f */
	vector<T<interval>> get_f(){return f;}

	/* Evaluate the j'th Taylor coefficient of x */
	void x_eval(int j);

	/* Set x */
	void set_x(v_interval v, int i);

	/* Reset the ODE */
	void reset();

	/* Compute all the n-1 first Taylor coefficients of xi and the n'th Taylor coefficient of B*/
	vector<vector<interval>> taylor_coefficients(v_interval xi, v_interval B, int n);
};



#endif