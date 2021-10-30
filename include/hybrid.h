

#ifndef HYBRID_H
#define HYBRID_H


#include "ode.h"

/* System states number */
extern int STATES;


class State
{
private:
	int                            num;
	v_interval                     enclosure;

public:
	/* Constructors */
	State(){}
	State(int num, v_interval enclosure){
		this->num = num;
		this->enclosure = enclosure;
	}

	/* Gets */
	int get_num(){return num;}
	v_interval get_enclosure(){return enclosure;}

	/* Sets */
	void set_num(int num){this->num = num;}
	void set_enclosure(v_interval enclosure){this->enclosure = enclosure;}
};

typedef v_interval (* functionMod)(v_interval arg);

class Hybrid
{
private:
	vector<State>                 enclosure;
	vector<ODE>                   system = vector<ODE>(STATES);
	vector<v_interval>           inGards = vector<v_interval>(STATES);
	vector<vector<v_interval>>  outGards = vector<vector<v_interval>>(STATES);
	vector<vector<functionMod>>  outMod = vector<vector<functionMod>>(STATES);

public:
	/* Constructors */
	Hybrid(){}
	Hybrid(vector<ODE> system, vector<v_interval> inGards, vector<vector<v_interval>> outGards, vector<vector<functionMod>> outMod, vector<State> enclosure);

	/* Gets */
	State get_enclosure(int i){return enclosure[i];}
	int get_enclosure_size(){return enclosure.size();}
	v_interval get_inGards(int i){return inGards[i];}
	v_interval get_outGards(int i, int j){return outGards[i][j];}
	functionMod get_outMod(int i, int j){return outMod[i][j];}
	ODE get_system(int i){return system[i];}


	void clear_enclosure(){enclosure.clear();}
	void enclosure_pushback(State s){enclosure.push_back(s);}
};
 
#endif