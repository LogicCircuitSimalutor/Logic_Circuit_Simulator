#include <iostream>
#include <vector>
#include "Gate.h"

using namespace std;

ostream& operator<<(ostream& out, const Gate& g){
	g.print(out);
	return out;
}

Gate::~Gate(){
	delete &m_input;
	delete &m_output;
} 

void Gate::print(ostream& out) const {
	out << "INPUT VECTOR" << endl;
	vector <Gate * >::const_iterator itr = m_input.begin();
	while(itr != m_input.end()){
		Gate * tmp = *itr;
		out << "\t connected from " << tmp->getName() << " with logic state " << tmp->getLogicState() <<endl;
		itr++;
	}

	out << "OUTPUT VECTOR" << endl;
	itr = m_output.begin();
	while(itr != m_output.end()){
		Gate * tmp = *itr;
		out << "\t connected to " << tmp->getName() << " with logic state " << this->getLogicState() <<endl;
		itr++;
	}
}

void Gate::addInput(Gate* g){
	m_input.push_back(g);
}

void Gate::addOutput(Gate* g){
	m_output.push_back(g);
}

void Gate::changeDeltaOnOutput(){
	vector <Gate * >::const_iterator itr = m_output.begin();
	while(itr != m_output.end()){
		Gate * tmp = *itr;
		tmp->setDelta(1);
		itr++;
	}
}

void Gate::CalculateOutput() {

}