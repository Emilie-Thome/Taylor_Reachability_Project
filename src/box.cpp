#include "box.h"

v_interval Box::phi(ODE ode, v_interval xi){
	v_interval phi_B(DIM);

	ode.reset();								// Reset the DAG
	ode.set_x(B, 0);							// Set x as B in the DAG
	ode.x_eval(1);								// Compute f(B)

	for (int j = 0; j < DIM; j++){				// B = xi + [0, h]*f(B)
		phi_B[j] = xi[j] + interval(0, h) * ode.get_f()[j][0];
	}

	return phi_B;
}

void Box::widen(double alpha){
	for (int j = 0; j < DIM; j++){				// Enlarge B and diminish h
		B[j] = B[j] + interval(-alpha, alpha) * B[j];
	}	
	h = h / 2;
}

bool Box::inclusion_reached(ODE ode, v_interval xi){
	v_interval phi_B = phi(ode, xi);

	for (int j = 0; j < DIM; j++){
		if (not phi_B[j].subset(B[j]))			// Look at every dimension
			return false;
	}

	return true;
}

bool Box::tolerance_reached(ODE ode, v_interval xi, double epsilon){
	bool ans = true;
	v_interval phi_B = phi(ode, xi);

	for (int j = 0; j < DIM; j++){
		double diff_width = abs(B[j].width() - phi_B[j].width());
		ans = ans && (diff_width < epsilon);
	}
	return ans;
}

void Box::bounding_box(ODE ode, v_interval xi, double step, double epsilon, double alpha){
	h = step;									// Set h as step in the bounding box
	B = xi;
	B = phi(ode, xi);

	/* Finding a bouncing box*/
	while (not inclusion_reached(ode, xi)){		// Check if xi + [0, h]*f(B) in B
			widen(alpha);
	}
	/* Reducing the bouncing box*/
	int iter = 0;
	while (not (tolerance_reached(ode, xi, epsilon)) and (iter < MAX_ITER)){	// Check the tolerance is reached
		iter++;
		B = phi(ode, xi);
	}
	// This permit to avoid infinite loops
	if (iter >= MAX_ITER){
		printf("Tolerance not reached for the bouncing box computation\n");
	}
}