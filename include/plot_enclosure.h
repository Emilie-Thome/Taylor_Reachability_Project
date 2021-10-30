

#ifndef PLOT_H
#define PLOT_H

#include "ode.h"


class Plot
{
private:
	vector<vector<double>> Xinf = vector<vector<double>>(DIM);
	vector<vector<double>> Xsup = vector<vector<double>>(DIM);
	vector<double> T;

public:
	void store(v_interval xi, double t);

	void pause(double t);

	void show();
};


#endif