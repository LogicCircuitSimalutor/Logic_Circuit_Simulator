#include <iostream>
#include <vector>
#include "OutputGate.h"

void OutputGate::print(ostream& out) const{
	out << "\t\t ===== INPUT ===== " << endl;
	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	Gate::print(out);
}

OutputGate::~OutputGate(){

}

void OutputGate::connectGate(Gate* g){
	 this->addOutput(g);

	 g->addInput(this);

}
