#ifndef _CIRCUIT_H_
#define _CIRCUIT_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Gate.h"

using namespace std;

class Circuit {
	string m_name;
	int m_level;
	vector <Gate * > m_gates;
	vector <Gate * > m_inputs;
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

	const vector <Gate * >* getGatesVector() const{
		return &m_gates;
	}

	const vector <Gate *>* getInputsVector() const{
		return &m_inputs;
	}

	const map<int, vector<Gate*>>* getGateSorted() const{
		return &m_gateSorted;
	}

	Gate * getGate(const string & name) const;

	void print(ostream& out) const;

	bool addGate(Gate* g);

	bool addInput(Gate* i);

	bool deleteGate(const string & name);

	bool checkGlobalConnection();

	bool calculateDelta() const;

	bool sortGate(); //todo --> done

	void simulate() const; //todo

	void applyInputs() const; //todo

	//fonction test unicité nom

	friend ostream& operator<<(ostream& out, Circuit &c){
		c.print(out);
		return out;
	}

};

#endif