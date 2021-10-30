

#ifndef BOX_H
#define BOX_H


#include "ode.h"

const int MAX_ITER = 100;

/* Bounding Box class */
class Box
{
private:
	double           h;          		// Box size over t
	v_interval B = v_interval(DIM);     // Box interval over x

	/* Compute Xi + f(B) */
	v_interval phi(ODE ode, v_interval xi);

	/* Widen B */
	void widen(double alpha);

	/* Return true if phi(B) is included in B */
	bool inclusion_reached(ODE ode, v_interval xi);

	/* Return true if the tolerance is reached */
	bool tolerance_reached(ODE ode, v_interval xi, double epsilon);

public:
	/* Get B and h*/
	v_interval get_B(){return B;}
	double get_h(){return h;}

	/* Bounding Box algorithm */
	void bounding_box(ODE ode, v_interval xi, double step, double epsilon, double alpha);
};


#endif