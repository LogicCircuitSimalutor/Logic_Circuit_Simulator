#include <iostream>
#include <vector>
#include "InputGate.h"

void InputGate::print(ostream& out) const{
	out << "\t\t ===== INPUT ===== " << endl;
	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	Gate::print(out);
}

InputGate::~InputGate(){

}

void InputGate::connectGate(Gate* g){
	 this->addOutput(g);

	 g->addInput(this);

}