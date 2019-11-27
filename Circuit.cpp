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

// void Circuit::sortGate() const{
// 	int level = 0;
// 	int compteurGate = 0;
// 	int compteurInput = 0;
// 	list <string> sortName;
// 	list <string> temp;

// 	//Niveau 0
// 	vector <Gate*>::const_iterator itr = m_inputs.begin();
// 	while(itr != m_inputs.end()){
// 		Gate* tmp = *itr;
// 		sortName.push_back(tmp->getName());
// 		itr++;
// 	}

// 	//Parcours des gates du circuit
// 	itr = m_gates.begin();
// 	while(itr != m_gates.end()){
// 		Gate* tmp = *itr;
// 		const vector <Gate *>* input = tmp->getInput();
// 		vector <Gate *>::const_iterator itr_gate = input->begin();

// 		cout << "Parcours de la porte : " <<endl;
// 		cout << tmp->getName() << endl;
// 		//Parcours Inputs par Gate
// 		while(itr_gate != input->end()){
// 			 Gate * tmp_gate = *itr_gate;
			
			 
// 			//comparaison avec le nom des précédentes portes
// 			list <string>::iterator itr_name = sortName.begin();
// 				while(itr_name != sortName.end()){
// 					Gate * tmp_gate = *itr_gate;
// 					cout << "Nom de l'entrée de sortName : " << endl;
// 					cout << *itr_name << endl;
// 					cout << "Nom de l'entrée de input vector : " << endl;
// 					cout << tmp_gate->getName() << endl;
// 						if(*itr_name == tmp_gate->getName()){
// 							cout << "Les noms sont semblables" << endl;
// 							compteurInput++;
// 							//itr_gate++;
// 						}
// 						itr_name++;
// 				}
// 			itr_gate++;
// 		}
// 						cout << compteurInput << endl;

// 				if(compteurInput == tmp->getNbInput()){
// 					temp.push_back(tmp->getName());
// 				}
// 				compteurInput = 0;
// 		itr++;
// 	}

// 	list <string>::iterator itr_name = temp.begin();
// 	while(itr_name != temp.end()){
// 		sortName.push_back(*itr_name);
// 		itr_name++;
// 	}
// 	temp.clear();

// 	cout << "Affichage des noms après un tour de tri ! " << endl;
// 	itr_name = sortName.begin();
// 	while(itr_name != sortName.end()){
// 		cout << *itr_name << endl;
// 		itr_name++;
// 	}



// }

// bool Circuit::sortGate() const{
// 	int compteurGate = 0;
// 	int compteurInput = 0;
// 	list <string> sortName;
// 	list <string> temp;
// 	int sizeGatesInputs = m_inputs.size() + m_gates.size();

// 	//Niveau 0
// 	vector <Gate *>::const_iterator itr = m_inputs.begin();
// 	while(itr != m_inputs.end()){
// 		Gate* tmp = *itr;
// 		sortName.push_back(tmp->getName());
// 		itr++;
// 	}

// 	/*>Tant que toutes les portes ne sont pas triées */
// 	while(sortName.size() != sizeGatesInputs){

// 		itr = m_gates.begin();

// 		/*>Parcours de toutes les portes */
// 		while(itr != m_gates.begin()){
// 			Gate* tmp = *itr;
// 			const vector <Gate*>* input = tmp->getInput(); //récupère la référence sur les inputs de la Gate
// 			vector <Gate*>::const_iterator itr_gate = input->begin();

// 			/*>Parcours des Inputs de la Gate */
// 			while(itr_gate != input->end()){
// 				Gate * tmp_gate = *itr_gate;

// 				/*>Compraison avec sortName */
// 				list <string>::iterator itr_name = sortName.begin();
// 				while(itr_name != sortName.end()){
// 					Gate * tmp_gate = *itr_gate;
// 					if(*itr_name != tmp_gate->getName()){
// 						itr_name++;
// 					}else{
// 						compteurInput++;
// 						itr_name = sortName.end();
// 					}
// 				}
// 				itr_gate++;
// 				if(compteurInput == tmp->getNbInput()){
// 					temp.push_back(tmp->getName());
// 					compteurGate++;
// 				}

// 			}

// 			if(!compteurGate){
// 				return false; //rebouclage combinatoire
// 			}
// 			itr_gate++;
// 		}
// 		list <string>::iterator itr_name = temp.begin();
// 		while(itr_name != temp.end()){
// 			sortName.push_back(*itr_name);
// 			itr_name++;
// 		}
// 		temp.clear();

// 	}
// 	itr_name = sortName.begin();
// 	while(itr_name != sortName.end()){
// 		cout << *itr_name << endl;
// 		itr_name++;
// 	}

// 	return true;


// }

bool Circuit::sortGate() const{
	int compteurGate = 0;
	int compteurInput = 0;
	int level = 1;
	list <string> sortName;
	int sizeGatesInput = m_inputs.size() + m_gates.size();

	vector <Gate*>::const_iterator itr = m_inputs.begin();
	while(itr != m_inputs.end()){
		Gate* tmp = *itr;
		sortName.push_back(tmp->getName());
		itr++;
	}

	//Parcours des portes
	while(int(sortName.size() ) != sizeGatesInput){
	cout << "Taille de sortName : " << sortName.size() << endl;
	cout << "Taille de sizeGatesInput : " << sizeGatesInput << endl;
		itr = m_gates.begin();

		/*>Parcours de toutes les portes*/
		while(itr != m_gates.end()){
			Gate* tmp = *itr;
			const vector <Gate*>* input = tmp->getInput(); //récupère la référence sur les inputs de la Gate
			vector <Gate*>::const_iterator itr_gate = input->begin();

			cout << "Parcours de la porte : " << tmp->getName() << endl;
			cout << "Level : " << level << endl;

			/*>On ne traite pas les portes déjà affectées */
			if(tmp->getLevel() > level){

			/*>Parcours des Inputs de la Gate */
			while(itr_gate != input->end()){
				Gate* tmp_input = *itr_gate;
				
					/*>Comparaison de niveau */
					cout << "Le niveau de la porte est : " << tmp->getLevel() << endl;
					cout << "Le niveau de l'input connecté est : " << tmp_input->getLevel() << endl;
					if(tmp_input->getLevel() < level){ //On check la prochaine input
						itr_gate++;
						compteurInput++;
					}else{
					itr_gate = input->end(); //on skip le test sur cette porte
					}
					cout << "Compteur Input : " << compteurInput << endl;
				}

			}
			if(compteurInput == tmp->getNbInput()){
				sortName.push_back(tmp->getName());
					cout << "Taille de sortName : " << sortName.size() << endl;
				compteurGate++;
				tmp->setLevel(level);
			}
			compteurInput = 0;
			itr++;
		}
		if(!compteurGate){
			cout << "Je suis là" << endl;
			return false; //rebouclage combinatoire
		}
		compteurGate = 0;
		level++;

	}
	list <string>::iterator itr_name = sortName.begin();
	while(itr_name != sortName.end()){
		cout << *itr_name << endl;
		itr_name++;
	}

	return true;


}