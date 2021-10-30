#include "experiment.h"
#include "box.h"

Experiment::Experiment(ODE ode, v_interval x0, int n, double h, double alpha, double t0, double t_end, double epsilon){
	this->n = n;
	this->h = h;
	this->alpha = alpha;
	this->t = t0;
	this->t_end = t_end;
	this->epsilon = epsilon;
	this->xi = x0;
	this->ode = ode;
}

Experiment::Experiment(Hybrid hybrid, v_interval x0, int n, double h, double alpha, double t0, double t_end, double epsilon){
	this->n = n;
	this->h = h;
	this->alpha = alpha;
	this->t = t0;
	this->t_end = t_end;
	this->epsilon = epsilon;
	this->xi = x0;
	this->hybrid = hybrid;
}

void Experiment::nextODE(){
	Polynome p = nextPolynome();
	xi = p.apply(p.get_maxValue());
	t = t + p.get_maxValue();
}

void Experiment::solveODE(){
	plot.store(xi, t);

	while (t < t_end){
		// Compute the enclosure of x'i+1:
		nextODE();
		plot.store(xi, t);

		for (int d = 0; d < DIM; d++){
			if (xi[d].isInfinite()){
				printf("Infinite reached in the ODE solving at t=%f.\n", t);
				t = t_end;
				break;
			}
		}

	}
	Experiment::print_enclosure();
	plot.show();
}

void Experiment::nextHybrid(){
	vector<Polynome> P;
	vector<int>      states;

	for (int i = 0; i < hybrid.get_enclosure_size(); i++){
		State current_state = hybrid.get_enclosure(i);

		v_interval xInState = intersection(current_state.get_enclosure(), hybrid.get_inGards(current_state.get_num()));
		if (not isEmpty(xInState)){
			// Set the ODE experiment:
			Experiment expODE = Experiment(hybrid.get_system(current_state.get_num()), xInState, n, h, alpha, t, t_end, epsilon);
			P.push_back(expODE.nextPolynome()); // Compute the polinomal enclosure of x'i+1 in the current state
			states.push_back(current_state.get_num());
		}


		v_interval xOutState = exclude(current_state.get_enclosure(), hybrid.get_inGards(current_state.get_num()));
		if (not isEmpty(xOutState)){
			for (int s = 0; s < STATES; s++){
				v_interval xInS = hybrid.get_outMod(current_state.get_num(),s)(intersection(xOutState, hybrid.get_outGards(current_state.get_num(),s)));
				if (not isEmpty(xInS)){
					// Set the ODE experiment:
					Experiment expODE = Experiment(hybrid.get_system(s), xInS, n, h, alpha, t, t_end, epsilon);
					P.push_back(expODE.nextPolynome()); // Compute the polinomal enclosure of x'i+1 in the current state
					states.push_back(s);
				}
			}
		}
	}

	/* Find min step (for which every polinomial enclosure is true) */
	double min_step = DBL_MAX;
	for (int i = 0; i < P.size(); i++){
		min_step = min(min_step, P[i].get_maxValue());
	}
	
	/* Compute polynomial application and union of results */
	hybrid.clear_enclosure();
	xi = v_interval(DIM, empty());
	for (int i = 0; i < P.size(); i++){
		/* Compute the enclosure of each reached state */
		State new_state;
		new_state.set_num(states[i]);
		new_state.set_enclosure(P[i].apply(min_step));
		hybrid.enclosure_pushback(new_state);

		/* xi is the enclosure that is printed */
		xi = vector_hull(xi, P[i].apply(min_step));
	}
	
	t = t + min_step;
}

void Experiment::solveHybrid(){
	plot.store(xi, t);

	while (t < t_end){
		// Compute the enclosure of x'i+1:
		nextHybrid();
		plot.store(xi, t);

		for (int d = 0; d < DIM; d++){
			if (xi[d].isInfinite()){
				printf("Infinite reached in the Hybrid system at t=%f.\n", t);
				t = t_end;
				break;
			}
		}

	}
	Experiment::print_enclosure();
	plot.show();
}

void Experiment::print_enclosure(){
	for (int j = 0; j < DIM; j++){
		cout << "x" << j << "(" << t << ") = " << xi[j] << endl;
	}
}

Polynome Experiment::nextPolynome(){
	Box box;
	box.bounding_box(ode, xi, h, epsilon, alpha);
	vector<v_interval> Ti = ode.taylor_coefficients(xi, box.get_B(), n);
	Polynome p = Polynome(Ti, box.get_h(), n);
	return p;
}

bool Experiment::isEmpty(v_interval xi){
	for (int d = 0; d < DIM; d++){
		if (xi[d].isEmpty()){
			return true;
		}
	}
	return false;
}

v_interval Experiment::intersection(v_interval x1, v_interval x2){
	v_interval ans = v_interval(DIM);
	for (int d = 0; d < DIM; d++){
		ans[d] = x1[d].intersect(x2[d]);
	}
	return ans;
}

v_interval Experiment::vector_hull(v_interval x1, v_interval x2){
	v_interval ans = v_interval(DIM);
	for (int d = 0; d < DIM; d++){
		ans[d] = x1[d].interval_hull(x2[d]);
	}
	return ans;
}

v_interval Experiment::exclude(v_interval x1, v_interval x2){
	v_interval ans = v_interval(DIM);

	for (int d = 0; d < DIM; d++){
		if (not x2[d].seq(entire())){
			interval part1 = interval(entire().inf(), x2[d].inf());
			interval part2 = interval(x2[d].sup(), entire().sup());
			ans[d] = (x1[d].intersect(part2)).interval_hull(x1[d].intersect(part1));
		} else {
			ans[d] = x1[d];
		}
	}

	return ans;
}

