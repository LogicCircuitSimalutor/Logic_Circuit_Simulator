#include <iostream>
#include <string>
#include <list>
#include "Circuit.h"

bool Circuit::checkGlobalConnection(){
	vector <Gate *>::const_iterator itr = m_gates.begin();
	while(itr != m_gates.end()){
		Gate * tmp = *itr;
		if(!(tmp->CheckNumberInputs())){
			return false;
		}
		itr++;
	}
	return true;
}

bool Circuit::calculateDelta(){
	vector <Gate *>::const_iterator itr = m_gates.begin();
	while(itr != m_gates.end()){
		Gate * tmp = *itr;
		if(tmp->getDelta()){
			return true;
		}
		itr++;
	}
	return false;
}

bool Circuit::addGate(Gate* g){
	m_gates.push_back(g);
	return true;
}

bool Circuit::addInput(Gate* i){
	m_inputs.push_back(i);
	return true;
}

bool Circuit::sortGate(map< int, vector<Gate *> >* gateSorted) const{
	int compteurGate = 0;
	int compteurInput = 0;
	int level = 0;
	int NumberSorted = m_inputs.size();
	vector <Gate*> levelSorted;
	int sizeGatesInput = m_inputs.size() + m_gates.size();

	vector <Gate*>::const_iterator itr = m_inputs.begin();
	while(itr != m_inputs.end()){
		Gate* tmp = *itr;
		levelSorted.push_back(tmp);
		itr++;
	}
	gateSorted->insert(pair<int, vector<Gate*>>(level,levelSorted));

	level++; //Start of Gates sorting

	//Parcours des portes
	while(NumberSorted != sizeGatesInput){
		levelSorted.clear();
		itr = m_gates.begin();

		/*>Parcours de toutes les portes*/
		while(itr != m_gates.end()){
			Gate* tmp = *itr;
			const vector <Gate*>* input = tmp->getInput(); //récupère la référence sur les inputs de la Gate
			vector <Gate*>::const_iterator itr_gate = input->begin();

			/*>On ne traite pas les portes déjà affectées */
			if(tmp->getLevel() > level){

			/*>Parcours des Inputs de la Gate */
			while(itr_gate != input->end()){
				Gate* tmp_input = *itr_gate;
				
					/*>Comparaison de niveau */
					if(tmp_input->getLevel() < level){ //On check la prochaine input
						itr_gate++;
						compteurInput++;
					}else{
					itr_gate = input->end(); //on skip le test sur cette porte
					}
				}

			}
			if(compteurInput == tmp->getNbInput()){
				NumberSorted++;
				compteurGate++;
				tmp->setLevel(level);
				levelSorted.push_back(tmp);
			}
			compteurInput = 0;
			itr++;
		}
		if(!compteurGate){
			return false; //rebouclage combinatoire
		}
		gateSorted->insert(pair<int, vector<Gate*>>(level,levelSorted));
		compteurGate = 0;
		level++;

	}
	return true;
}