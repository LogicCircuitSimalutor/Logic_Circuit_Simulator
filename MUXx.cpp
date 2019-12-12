#include <iostream>
#include <string>
#include <vector>
#include "MUXx.h"
#include <math.h>       /* pow */
#include <algorithm>    // std::reverse

MUXx::~MUXx(){

}

void MUXx::connectSel(Gate* Sel, int pos)
{
	m_vectorSel.push_back(Sel);
	this->addBitSelection(pos);
}

void MUXx::addBitSelection(int bit){
	m_selectBit.push_back(bit);
}

bool MUXx::checkNumberSelector(){
	if(getSizeInput() <= pow(2, getSizeSel()) && getSizeInput() >= pow(2, getSizeSel()-1)){
		return true;
	}else{
		cout << "ERROR : Number of selector doesn't macth with number of inputs" << endl;
		return false;
	}
}

void MUXx::CalculateOutput(){

	int value_sel=0;
	int itr =0;
	bool temp_output =0;
	int temp_bit = 0;
	const vector <int>* bitSelection = getSelectBit();
	vector <int>::const_iterator itr_select = bitSelection->begin();

	for(std::vector<Gate*>::iterator itrv=m_vectorSel.begin();itrv!=m_vectorSel.end();itrv++)
	{
		Gate * tmp = *itrv;
		temp_bit = *itr_select;
		value_sel += (pow(2,itr) * tmp->getLogicState(temp_bit)) ;
		itr++;
		itr_select++;
	}
	//cout << "value sel = " << value_sel << endl;

	// const vector <Gate *>* input = 

	if(value_sel >= getSizeInput()){
		cout << "Input " << value_sel << " is not connected" << endl;
		exit(101);
	}else{
		vector <Gate*>::const_iterator itr_gate = getInput()->begin() + value_sel;
		Gate * tmp_gate = *itr_gate;
		temp_output = tmp_gate->getLogicState(temp_bit);

	}

	// while(itr_gate != input->end()){
	// 	Gate * tmp_gate = *itr_gate;
	// 	if(tmp == value_sel)
	// 	{
	// 		temp_output=tmp_gate->getLogicState();
	// 		//itrv=input->end();
	// 	}
	// 	tmp++;
	// 	itr_gate++;
	// }

	if(temp_output != this->getLogicState(temp_bit)){
 		this->setLogicState(temp_output, temp_bit);
 		this->changeDeltaOnOutput();
	}

	setDelta(0);
}


void MUXx::print(ostream& out) const{

	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	out << "Level : " << this->getLevel() << endl;
	Gate::print(out);
	out << "VECTOR SEL" << endl;
	for(unsigned int itr= 0; itr!=m_vectorSel.size();itr++)
	{
			out << m_vectorSel[itr]->getName() << endl; //faut que ca sorte correctement le vector de sel
	}
}
