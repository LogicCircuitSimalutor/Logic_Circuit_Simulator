#ifndef _CIRCUIT_H_
#define _CIRCUIT_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Gate.h"
#include "build/VCDTypes.hpp"
#include "MUXx.h"
#include "OutputGate.h"

#include "Signal.h"
#include "Chronogramme.h"

using namespace std;

class Circuit {
	string m_name;
	int m_level;
	vector <Gate * > m_gates;
	vector <Gate * > m_inputs;
	vector <Gate * > m_outputs;
	vector <MUXx * > m_mux;
	map <int, vector <Gate*>> m_gateSorted;

public:

	Circuit(string name) : m_name(name), m_level(0){

	}

	~Circuit(){

	}

	void setName(const string name){
		m_name = name;
	}

	string getName() const{
		return m_name;
	}

	void setLevel(const int level){
		m_level = level;
	}

	int getLevel() const{
		return m_level;
	}

	int getNbGates() const{
		return m_gates.size();
	}

	const vector<MUXx * > * getMuxVector() const{
		return &m_mux;
	}

	const vector <Gate * >* getGatesVector() const{
		return &m_gates;
	}

	const vector <Gate *>* getInputsVector() const{
		return &m_inputs;
	}

	const vector <Gate *>* getOutputsVector() const{
		return &m_outputs;
	}

	const map<int, vector<Gate*>>* getGateSorted() const{
		return &m_gateSorted;
	}

	int getSizeOutput() const{
		return m_outputs.size();
	}

	Gate * getGate(const string & name) const;

	void print(ostream& out) const;

	bool addGate(Gate* g);

	bool addInput(Gate* i);
	// bool replace(Gate * g);
	bool addMux(MUXx* g);

	bool addOutput(Gate* o);

	bool deleteGate(const string & name);

	bool checkGlobalConnection();

	bool checkOutputConnected();

	bool calculateDelta() const;

	bool sortGate(); //todo --> done

	bool simulate(map<int, vector<bool> > * mapStimulis, Chronogramme& c, int period, ostream& out) const; //in progress

	void applyInputs(vector<bool>& InputValues) const; //todo --> done

	int findStartLevel() const;

	bool fillOutputsVector(vector<Signal*>* s, int x, int y);

	bool printOutput(ostream& out) const;

	friend ostream& operator<<(ostream& out, Circuit &c){
		c.print(out);
		return out;
	}

};

#endif
