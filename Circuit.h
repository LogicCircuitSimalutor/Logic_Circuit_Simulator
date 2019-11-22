#ifndef _CIRCUIT_H_
#define _CIRCUIT_H_

#include <iostream>
#include <string>
#include <vector>
#include "Gate.h"

using namespace std;

class Circuit {
	string m_name;
	vector <Gate * > m_gates;
	vector <Gate * > m_inputs;

public:

	Circuit(string name) : m_name(name){

	}

	~Circuit(){

	}

	void setName(const string name){
		m_name = name;
	}

	string getName() const{
		return m_name;
	}

	int getNbGates() const{
		return m_gates.size();
	}

	const vector <Gate * >* getGatesVector() const{
		return &m_gates;
	}

	const vector <Gate *>* getInputsVector() const{
		return &m_inputs;
	}

	Gate * getGate(const string & name) const;

	void print(ostream& out) const;

	bool addGate(Gate* g);

	bool deleteGate(const string & name);

	bool checkGlobalConnection();

	bool calculateDelta();

	void sortGate(); //todo

	void simulate(); //todo

	friend ostream& operator<<(ostream& out, Circuit &c){
		c.print(out);
		return out;
	}

};

#endif