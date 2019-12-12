/* Check number of inputs*/
#ifndef _GATE_H_
#define _GATE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Gate {

	string m_name;
	bool m_logicState;
	bool m_delta;
	vector <Gate*> m_input;
	vector <Gate*> m_output;
	vector <int> m_selectBit;
	int m_NbINput;
	int m_level;


public:

	//Définition des constructeurs
	Gate(string name, int NbInput, bool logicState = 0) : 
	m_name(name), 
	m_logicState(logicState),
	m_delta(1),
	m_NbINput(NbInput),
	m_level(5000000){

	}

	//Destructeur
	virtual ~Gate();

	//Accesseurs et getteurs

	void setName(const string name){
		m_name = name;
	}

	string getName() const{
		return m_name;
	}

	virtual void setLogicState(const bool logic, int pos = 0){
		m_logicState = logic;
	}

	virtual bool getLogicState(int pos = 0) const{
		return m_logicState;
	}

	void setDelta(const bool delta){
		m_delta = delta;
	}

	bool getDelta() const{
		return m_delta;
	}

	int getLevel() const{
		return m_level;
	}

	void setLevel(const int level){
		m_level = level;
	}

	const vector <Gate * >* getInput() const{
		return  &m_input;
	}

	const vector <Gate *>* getOutput() const{
		return &m_output;
	}

	const vector <int>* getSelectBit() const{
		return &m_selectBit;
	}

	void addInput(Gate* g);

	void addOutput(Gate* g);

	void addBitSelect(int pos);

	void changeDeltaOnOutput();

	bool CheckNumberInputs();

	int getSizeInput() const{
		return m_input.size();
	}

	int getSizeOutput() const{
		return m_output.size();
	}

	int getNbInput() const{
		return m_NbINput;
	}

	bool checkOutputVectorEmpty() const;

	virtual void connectGate(Gate* g, int pos) = 0;

	virtual void CalculateOutput();

	virtual void print(ostream& out) const;

	friend ostream& operator<<(ostream& out, const Gate &g);

};

#endif