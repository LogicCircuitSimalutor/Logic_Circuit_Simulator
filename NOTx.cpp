#include <iostream>
#include <string>
#include <vector>
#include "NOTx.h"

NOTx::~NOTx(){

}

void NOTx::CalculateOutput() {
	const vector <Gate * >* input = getInput();
	const vector <int>* bitSelection = getSelectBit();
	vector <Gate *>::const_iterator itr = input->begin();
	vector <int>::const_iterator itr_select = bitSelection->begin();
	Gate * tmp = *itr;
	int temp_bit = *itr_select;
	cout << "Temp_bit vaut : " << temp_bit << endl;
	bool temp_output = !(tmp->getLogicState(temp_bit));

	if(temp_output != this->getLogicState(temp_bit)){
		this->setLogicState(temp_output, temp_bit);
		this->changeDeltaOnOutput();
	}
	setDelta(0);


}


void NOTx::print(ostream& out) const{
	vector <int >::const_iterator itr = getSelectBit()->begin();
	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	out << "Bit value : " << *itr << endl;
	out << "Level : " << this->getLevel() << endl;
	Gate::print(out);
}