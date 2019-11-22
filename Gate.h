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
	int m_NbINput;


public:

	//Définition des constructeurs
	Gate(string name, int NbInput, bool logicState = 0) : 
	m_name(name), 
	m_logicState(logicState),
	m_delta(1),
	m_NbINput(NbInput){

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

	void setLogicState(const bool logic){
		m_logicState = logic;
	}

	bool getLogicState() const{
		return m_logicState;
	}

	void setDelta(const bool delta){
		m_delta = delta;
	}

	bool getDelta() const{
		return m_delta;
	}

	void setOutput(Gate &g){
		
	}

	void setInput(Gate &g){
		//push dans vector
	}

	const vector <Gate * >* getInput() const{
		return  &m_input;
	}

	const vector <Gate *>* getOutput() const{
		return &m_output;
	}

	void addInput(Gate* g);

	void addOutput(Gate* g);

	void changeDeltaOnOutput();

	bool CheckNumberInputs();

	int getSizeInput() const{
		return m_input.size();
	}

	int getNbInput() const{
		return m_NbINput;
	}

	virtual void connectGate(Gate* g) = 0;

	virtual void CalculateOutput();

	virtual void print(ostream& out) const;

	friend ostream& operator<<(ostream& out, const Gate &g);

};

#endif