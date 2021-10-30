#include "plot_enclosure.h"

/* include matplotlib for C++ */
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;



void Plot::store(v_interval xi, double t){
	for (int d = 0; d < DIM; d++){
		Xinf[d].push_back(xi[d].inf());
		Xsup[d].push_back(xi[d].sup());		
	}
	T.push_back(t);
}

void Plot::pause(double t){
	plt::clf();
	for (int d = 0; d < DIM; d++){
		plt::plot(T, Xinf[d], "r-", T, Xsup[d], "b-");
	}
	plt::grid();
	plt::pause(t);
}

void Plot::show(){
	for (int d = 0; d < DIM; d++){
		plt::plot(T, Xinf[d], "r-", T, Xsup[d], "b-");
	}
	plt::grid();
	plt::show();
}