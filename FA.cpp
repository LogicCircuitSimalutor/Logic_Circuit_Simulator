#include <iostream>
#include <string>
#include <vector>
#include "FA.h"

FA::~FA(){

}

void FA::CalculateOutput(){
	const vector <Gate * >* input = getInput();
	const vector <int>* bitSelection = getSelectBit();
	vector <Gate *>::const_iterator itr = input->begin();
	vector <int>::const_iterator itr_select = bitSelection->begin();
	Gate * tmp = *itr;
	int temp_bit = *itr_select;
	int compteur = 0;
	bool toto = 0;
	bool temp_output = tmp->getLogicState(temp_bit);
	if(temp_output){
		compteur++;
	}
	itr++;

	while(itr != input->end()){
		Gate * tmp = *itr;
		temp_bit = *itr_select;
		temp_output = temp_output ^ tmp->getLogicState(temp_bit);
		if(tmp->getLogicState(temp_bit)){
			compteur++;
		}
		itr++;
	}
	if(temp_output != this->getLogicState(0)){
		this->setLogicState(temp_output, 0);
		this->changeDeltaOnOutput();
	}
	cout << "Compteur vaut : " << compteur << endl;
	if(compteur >= 2){
		toto = 1;
	}else{
		toto = 0;
	}
	if(toto != this->getLogicState(1)){
		this->setLogicState(toto, 1);
		this->changeDeltaOnOutput();
	}
	cout << "toto = " << toto << endl;
	setDelta(0);
}


void FA::print(ostream& out) const{

	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState(0) << endl;
	out << "Cout value : " << this->getLogicState(1) << endl;
	out << "Delta value : " << this->getDelta() << endl;
	out << "Level : " << this->getLevel() << endl;
	Gate::print(out);
}