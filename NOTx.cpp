#include <iostream>
#include <string>
#include <vector>
#include "NOTx.h"

NOTx::~NOTx(){

}

void NOTx::CalculateOutput() {
	const vector <Gate * >* input = getInput();
	vector <Gate *>::const_iterator itr = input->begin();
	Gate * tmp = *itr;
	bool temp_output = !(tmp->getLogicState());

	if(temp_output != this->getLogicState()){
		this->setLogicState(temp_output);
		tmp->changeDeltaOnOutput();
	}
	setDelta(0);


}


void NOTx::print(ostream& out) const{

	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	out << "Level : " << this->getLevel() << endl;
	Gate::print(out);
}