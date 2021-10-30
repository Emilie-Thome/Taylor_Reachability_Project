#include "ode.h"

/* System dimension */
int DIM = 10;

ODE::ODE(functionODE func){
	this->func = func;
	f = func(x);
}

void ODE::x_eval(int j){
	for (int d = 0; d < DIM; d++){
		f[d].eval(j - 1);
		x[d][j] = f[d][j - 1]/double(j);
	}
}

void ODE::set_x(v_interval v, int i){
	for (int d = 0; d < DIM; d++){
		x[d][i] = v[d];
	}
}

void ODE::reset()
{
	for (int d = 0; d < DIM; d++){
		f[d].reset();
	}
	ODE(func);
}

vector<vector<interval>> ODE::taylor_coefficients(v_interval xi, v_interval B, int n){
	reset();						// Reset the DAG
	set_x(xi, 0);					// Set point of expansion:

	vector<v_interval> ans(DIM);
	for (int d = 0; d < DIM; d++){
		ans[d].push_back(xi[d]);
	}

	for (int j = 1; j < n; j++){
		x_eval(j);					// Evaluate the j'th Taylor coefficient
		for (int d = 0; d < DIM; d++){
			ans[d].push_back(x[d][j]);
		}
	}

	reset();						// Reset the DAG
	set_x(B, 0);					// Set point of expansion:
	for (int j = 1; j < n + 1; j++){
		x_eval(j);					// Evaluate the j'th Taylor coefficient
	}
	for (int d = 0; d < DIM; d++){
		ans[d].push_back(x[d][n]);
	}

	return ans;
}