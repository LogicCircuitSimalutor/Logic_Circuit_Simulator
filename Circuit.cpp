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

bool Circuit::calculateDelta() const{
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

void Circuit::applyInputs(vector<bool>& InputValues) const{
	vector <bool>* InputStimuli = &InputValues;
	vector <bool>::const_iterator itr_sti = InputStimuli->begin();

	vector <Gate*>::const_iterator itr = m_inputs.begin();
	while(itr != m_inputs.end()){
		Gate* tmp = *itr;
		if(itr_sti != InputStimuli->end()){ //on vérifie qu'on ne dépasse pas la taille du vecteur
			cout << "Valeur du booléen à appliquer : " << *itr_sti << endl;
			if(tmp->getLogicState() != *itr_sti)
			{
				tmp->setLogicState(*itr_sti);
				cout << "Valeur de l'entrée : " << tmp->getLogicState() << endl;
				tmp->setDelta(1);
			}
			itr_sti++;
		}
		itr++;
	}

}

int Circuit::findStartLevel() const{

	map <int, vector <Gate*>>::const_iterator itr = m_gateSorted.begin();
	for (itr++ ; itr != m_gateSorted.end(); itr++) { 
        vector <Gate*>::const_iterator itr_vector = itr->second.begin();
		while(itr_vector != itr->second.end()){
			Gate* tmp_gate = *itr_vector;
			if(tmp_gate->getDelta()){ //si le delta de la porte est true
				return tmp_gate->getLevel();
			}else{
				itr_vector++;
			} 
		} 
    }
    return 0; //erreur lors de la recherche de niveau


}

bool Circuit::sortGate(){
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
	m_gateSorted.insert(pair<int, vector<Gate*>>(level,levelSorted));

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
		m_gateSorted.insert(pair<int, vector<Gate*>>(level,levelSorted));
		compteurGate = 0;
		level++;

	}
	return true;
}

bool Circuit::simulate(map<int, vector<bool> > * mapStimulis) const{
	//We start simulation at startLevel, that means we skip level we stay unchanged
	int startLevel = 1;
	//Clock Time cycle
	int clockCycle =0;

	map<int, vector<bool> >* Stimulis = mapStimulis;
	map<int, vector<bool> >::iterator itr_clock = Stimulis->begin();

	//Loop on map stimuli
	while(itr_clock != Stimulis->end()){
		if(itr_clock->first != clockCycle){
			clockCycle++;
			itr_clock++;
		}else{
			/*>Application des stimuli */
			applyInputs(itr_clock->second);
			/*> Calcul de Delta if delta = 0 ==> next stimuli else calculation */
			if(calculateDelta()){
				/*>Recherche de la première entrée modifiée */

				/*>Calcul de startLevel*/
				startLevel = findStartLevel();
				if(startLevel){ //on retourne un niveau correct

					map <int, vector <Gate*>>::const_iterator itr = m_gateSorted.begin();
					for(int i = 0 ; i < startLevel ; i++){
						itr++;
					}

					for ( ; itr != m_gateSorted.end(); itr++) { 
        				vector <Gate*>::const_iterator itr_vector = itr->second.begin();
						while(itr_vector != itr->second.end()){
							Gate* tmp_gate = *itr_vector;
							tmp_gate->CalculateOutput();
							itr_vector++;
						} 
    				}

				}else{
					return false; //il y a une erreur dans la recherche de niveau
				}

			}else{
				//next stimuli
				//on garde la dernière valeur de sortie
			}
			itr_clock++;
			clockCycle++;

		}
	}

	return true; //la simulation a fonctionné
}