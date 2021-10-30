#include "hybrid.h"

/* System states number */
int STATES   = 10;

Hybrid::Hybrid(vector<ODE> system, vector<v_interval> inGards, vector<vector<v_interval>> outGards, vector<vector<functionMod>> outMod, vector<State> enclosure){
	this->system = system;
	this->inGards = inGards;
	this->outGards = outGards;
	this->outMod = outMod;
	this->enclosure = enclosure;
}