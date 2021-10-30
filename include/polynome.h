

#ifndef POLYNOME_H
#define POLYNOME_H

#include "ode.h"


class Polynome
{
private:
	vector<v_interval>    coefficients;
	double                maxValue;
	int                   degre;

public:
	/* Constructor */
	Polynome(vector<v_interval> coefficients, double maxValue, int degre){
		this->coefficients = coefficients;
		this->maxValue = maxValue;
		this->degre = degre;
	}

	/* Get */
	double get_maxValue(){return maxValue;}

	/* Application */
	v_interval apply(double t){
		if (t > maxValue){
			printf("Warning, this enclosure is not true.\n");
		}
		v_interval x = v_interval(DIM);

		for (int d = 0; d < DIM; d++){
			interval coef = interval(1.);
			x[d] = interval(0.);
			for (int j = 0; j < degre+1; j++){
				x[d] = x[d] +  coef * coefficients[d][j];
				coef = coef * interval(t);
			}
		}

		return x;
	}

};


#endif