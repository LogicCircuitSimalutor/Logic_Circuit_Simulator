#include <iostream>
#include <string>
#include <list>
#include "Circuit.h"

using namespace std;

void Circuit::print(ostream& out) const{
	vector <Gate *>::const_iterator itr = m_gates.begin();
		while(itr != m_gates.end()){
		Gate * tmp = *itr;
		out << *tmp << endl;
		itr++;
	}
}

bool Circuit::checkGlobalConnection(){
	vector <Gate *>::const_iterator itr_in = m_inputs.begin();
	vector <Gate *>::const_iterator itr = m_gates.begin();
	vector <MUXx * >::const_iterator itr_mux = m_mux.begin();
	while(itr_mux != m_mux.end()){
		MUXx * tmp = *itr_mux;
		if(!(tmp->checkNumberSelector())){
			return false;
		}
		itr_mux++;
	}
	while(itr != m_gates.end()){
		Gate * tmp = *itr;
		if(!(tmp->CheckNumberInputs())){
			return false;
		}
		itr++;
	}
	while(itr_in != m_inputs.end()){
		Gate* tmp = *itr_in;
		if(tmp->getSizeInput()){
			cout << "An Input can't be connected in input" << endl;
			return false;
		}
		itr_in++;
	}
	if(!(m_inputs.size()) or !(m_gates.size())){
		cout << "Circuit can't be empty" << endl;
		return false;
	}
	cout << "La taille de vector m_outputs est " << m_outputs.size() << endl;
	if(!(m_outputs.size())){
		cout << "Circuit must have at least one output" << endl;
		return false;
	}
	if(!(checkOutputConnected())){
		return false;
	}
	return true;
}

bool Circuit::checkOutputConnected(){
	vector <Gate *>::const_iterator itr = m_outputs.begin();
	while(itr != m_outputs.end()){
		Gate * tmp = *itr;
		cout << "Number input " << tmp->CheckNumberInputs() << endl;
		if(!(tmp->CheckNumberInputs())){
			cout << "Output must be connected" << endl;
			return false;
		}
		itr++;
	}
	return true;
}

bool Circuit::calculateDelta() const{
	vector <Gate *>::const_iterator itr = m_gates.begin();
	vector <Gate *>::const_iterator itr_out = m_outputs.begin();
	while(itr != m_gates.end()){
		Gate * tmp = *itr;
		if(tmp->getDelta()){
			//cout << "Delta vaut : " << tmp->getDelta() << endl;
			return true;
		}
		itr++;
	}
	while(itr_out != m_outputs.end()){
		Gate * tmp = *itr_out;
		if(tmp->getDelta()){
			//cout << "Delta vaut : " << tmp->getDelta() << endl;
			return true;
		}
		itr_out++;
	}
	return false;
}

bool Circuit::addGate(Gate* g){
	m_gates.push_back(g);
	return true;
}

bool Circuit::addMux(MUXx * g){
	m_mux.push_back(g);
	return true;
}

// bool Circuit::replace(Gate * g)
// {
// 	string name = g->getName();
// 	for(std::vector<Gate*>::iterator it =m_inputs.begin(); it!=m_inputs.end(); ++it)
// 	{
// 		Gate * tmp = *it;
// 		if(tmp->getName() == g->getName())
// 		{
// 			MUXx mtoto = new MUXx(g->getName(),g->getNbInput());
// 			vector <Gate *> toto = tmp->getVectorSel();
// 			m_inputs.erase(it);
// 			m_inputs.push_back(g);
// 			return 1;
// 		}
// 	}
// 	for(std::vector<Gate*>::iterator it =m_gates.begin(); it!=m_gates.end(); ++it)
// 	{
// 		Gate * tmp = *it;
// 		if(tmp->getName() == g->getName())
// 		{
// 			m_gates.erase(it);
// 			m_gates.push_back(g);
// 			return 1;
// 		}
// 	}
// 	return 0;
// }

bool Circuit::addInput(Gate* i){
	m_inputs.push_back(i);
	return true;
}

bool Circuit::addOutput(Gate* o){
	m_outputs.push_back(o);
	return true;
}

void Circuit::applyInputs(vector<bool>& InputValues) const{
	vector <bool>* InputStimuli = &InputValues;
	vector <bool>::const_iterator itr_sti = InputStimuli->begin();

	vector <Gate*>::const_iterator itr = m_inputs.begin();
	while(itr != m_inputs.end()){
		Gate* tmp = *itr;
		if(itr_sti != InputStimuli->end()){ //on vérifie qu'on ne dépasse pas la taille du vecteur
			// cout << "Valeur du booléen à appliquer sur : " << tmp->getName() << " vaut : " << *itr_sti << endl;
			if(tmp->getLogicState(0) != *itr_sti)
			{
				tmp->setLogicState(*itr_sti);
				// cout << "Valeur de l'entrée de la porte : " << tmp->getLogicState() << endl;
				tmp->changeDeltaOnOutput();
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

// bool Circuit::fillOutputsVector(vector<Signal*>* s, int x, int y){
// 	vector <Gate *>::const_iterator itr = m_inputs.begin();
// 	while(itr != m_inputs.end()){
// 		Gate * tmp = *itr;
// 		x = x + 40;
// 		s->push_back(new Signal(x,y,tmp));
// 		itr++;
// 	}
// 	itr = m_gates.begin();
// 	while(itr != m_gates.end()){
// 		Gate * tmp = *itr;
// 		if(!(tmp->getSizeOutput())){
// 			this->addOutput(tmp);
		
// 			x = x + 40;
// 			s->push_back(new Signal(x,y,tmp));
// 		}
// 		itr++;
// 	}

// 	if(!(m_outputs.size())){
// 		return false; //not possible to have a circuit without output
// 	}else{
// 		return true;
// 	}

// }

bool Circuit::fillOutputsVector(vector<Signal*>* s, int x, int y){
	vector <Gate *>::const_iterator itr = m_inputs.begin();
	while(itr != m_inputs.end()){
		Gate * tmp = *itr;
		x = x + 40;
		s->push_back(new Signal(x,y,tmp));
		itr++;
	}
	itr = m_outputs.begin();
	while(itr != m_outputs.end()){
		Gate * tmp = *itr;
			x = x + 40;
			s->push_back(new Signal(x,y,tmp));
		itr++;
	}

	if(!(m_outputs.size())){
		return false; //not possible to have a circuit without output
	}else{
		return true;
	}

}

bool Circuit::printOutput(ostream& out) const{
	if(!(m_outputs.size())){
		return false; //not possible to have a circuit without output
	}else{
		vector <Gate *>::const_iterator itr = m_inputs.begin();
		while(itr != m_inputs.end()){
			Gate * tmp = *itr;
			out << tmp->getName() << " : " << tmp->getLogicState() << endl;
			itr++;
		}
		itr = m_outputs.begin();
		//cout << "La taille de outputs vector est : " << m_outputs.size() << endl;
		while(itr != m_outputs.end()){
			Gate * tmp = *itr;
			out << tmp->getName() << " : " << tmp->getLogicState() << endl;
			itr++;
		}
		out << endl;
	}
	return true;
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
	levelSorted.clear();
	itr = m_outputs.begin();
	while(itr != m_outputs.end()){
		Gate* tmp = *itr;
		tmp->setLevel(level);
		levelSorted.push_back(tmp);
		itr++;
	}
	m_gateSorted.insert(pair<int, vector<Gate*>>(level,levelSorted));
	return true;
}

bool Circuit::simulate(map<int, vector<bool> > * mapStimulis, Chronogramme& c, int period,ostream& out) const{
	//We start simulation at startLevel, that means we skip level which stay unchanged
	int startLevel = 1;
	//Clock Time cycle
	int clockCycle = 0;

	map<int, vector<bool> >* Stimulis = mapStimulis;
	map<int, vector<bool> >::iterator itr_clock = Stimulis->begin();

	/* ================= READ MAP STIMULI ===================== */
	while(itr_clock != Stimulis->end()){
		//cout << "VCDTime : " << itr_clock->first << endl;
		//cout << "ClockCycle : " << clockCycle << endl;

		/*> ================ START OF SIMULATION FOR ONE CYCLE ======================= */

		/*> CHECK IF STIMULI AT CLOCK CYCLE */
		if(itr_clock->first != clockCycle){
			/*>Wait for next clock cycle */
			clockCycle++;
		}else{
			/*> FOR FIRST CLOCK CYCLE, CIRCUIT IS FULL EVALUATED */
			if(clockCycle == 0){
				//cout << "Clock 0" << endl;

				/*>Application des stimuli */
				applyInputs(itr_clock->second);

				/*> EVEN IF ALL DELTA OF EACH GATE IS DEFAULT VALUE 1, WE CHECK IF GLOBAL DELTA IS TRUE */
				if(calculateDelta()){
				/*>Recherche de la première entrée modifiée */
				/*>Calcul de startLevel*/

				startLevel = findStartLevel();

				/*>START FROM LEVEL WHERE DELTA DIFFERENT OF 0*/
				if(startLevel){ //if we find a level different of 0
					/*> ================= EVALUATION OF CIRCUIT ================================ */

					map <int, vector <Gate*>>::const_iterator itr = m_gateSorted.begin();
					for(int i = 0 ; i < startLevel ; i++){
						itr++;
					}

					for ( ; itr != m_gateSorted.end(); itr++) {
        				vector <Gate*>::const_iterator itr_vector = itr->second.begin();
						while(itr_vector != itr->second.end()){
							Gate* tmp_gate = *itr_vector;

							// cout << "Nom de la porte calculée : " << tmp_gate->getName() << endl;
							/*> Evaluate only gate with delta non equal to zero */
							if(tmp_gate->getDelta()){
								tmp_gate->CalculateOutput();

							}
							// cout << "Sortie de " << tmp_gate->getName() << " = " << tmp_gate->getLogicState() << endl;
							itr_vector++;
						}
    				}
    				itr_clock++;

    				/*> ================== END OF EVALUATION ================================= */

    				/*> ERROR WITH SEARCH LEVEL */
					}else{
						cout << "Search start level failed .... " << endl;
						return false; //error during searching of level to start
					}

				/*> DELTA IS NULL, NO GATE NEED TO BE EVALUATED, WAIT FOR NEXT STIMULI, INCREMENT CLOCK CYCLE */
				}else{
					itr_clock++;
					//clockCycle++;
					//keep last output value

				}
				//clockCycle++;

				/*> FOR NEXT CLOCK CYCLE DIFFERENT OF 0, EVALUATE ONLY MANDATORY STAGE */
			}else{
				//cout << "Clock différente de 0" << endl;
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
								// cout << "Nom de la porte calculée : " << tmp_gate->getName() << endl;
								/*> Evaluate only gate with delta non equal to zero */
								if(tmp_gate->getDelta()){
									tmp_gate->CalculateOutput();
								}

								itr_vector++;

							}
    					}

    				//clockCycle++;
    				itr_clock++;
					}else{
						cout << "Search start level failed .... " << endl;
						return false; //error during searching of level to start
					}

				}else{
					itr_clock++;
					//clockCycle++;
					//next stimuli
					//on garde la dernière valeur de sortie
				}

			}
			/*> ================ END OF SIMULATION FOR ONE CYCLE ======================= */
    		/*> next clock cycle */
    		clockCycle++;
		}
		/*> print output of circuit */
		//cout << "CLK" << clockCycle - 1<< endl;
		out << "Time : " << clockCycle-1 << endl;
		printOutput(out);
		c.TraceChronogramme(clockCycle-1);
	}
	/*===================== END OF READING STIMULI ========================= */

	return true; //simulation finished without errors
}
