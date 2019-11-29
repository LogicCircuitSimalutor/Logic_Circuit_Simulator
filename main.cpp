#include "Parseur.h"
#include "ParseurVCD.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>



using namespace std;

int main(int argc, char const *argv[]) {
  string dot_path = argv[1];
  string vcd_path = argv[2];



    Parseur parseur(dot_path);
    parseur.Parser();
    cout << parseur;
// cout << "Circuit dot ====== " << parseur.getCircuit() <<endl;
    ParseurVCD parseurVCD(vcd_path);
    parseurVCD.connectCircuit(parseur.getCircuit());
    parseurVCD.Parser();
    cout << parseurVCD;

  //
  // VCDFileParser parser;
  //
  // VCDFile *trace = parser.parse_file(vcd_path);
  //
  // if (trace)
  // {
  //     std::cout << "Parse successful." << std::endl;
  //     std::cout << "Version:       " << trace->version << std::endl;
  //     std::cout << "Date:          " << trace->date << std::endl;
  //     std::cout << "Signal count:  " << trace->get_signals()->size() << std::endl;
  //     std::cout << "Times Recorded:" << trace->get_timestamps()->size() << std::endl;
  //
  //     // Print out every signal in every scope.
  //     for (VCDScope *scope : *trace->get_scopes())my_signals
  //     {
  //
  //         std::cout << "Scope: " << scope->name << std::endl;
  //
  //         for (VCDSignal *signal : scope->signals)
  //         {
  //
  //
  //           //vectorInput=Parseur.getvectorInput();
  //           //if(signal->reference != )
  //             std::cout << "\t" << signal->hash << "\t"
  //                       << signal->reference;
  //
  //
  //             if (signal->size > 1)
  //             {
  //                 std::cout << " [" << signal->size << ":0]";
  //             }my_signals
  //
  //             std::cout << std::endl;
  //         }
  //       }
  //       std::cout << "Looking for signals" <<std::endl;
  //       auto my_signals =  trace->get_signals();
  //       std::cout << "Looking for timestamps" <<std::endl;
  //     auto  my_timestamps = trace->get_timestamps();
  //      int i=0;
  //      map<VCDTime, vector<VCDBit> > mapStimulis;
  //     for (VCDTime instant : *my_timestamps)
  //       {
  //         vector<VCDBit> vectorStimulis;
  //         vectorStimulis.clear();
  //         for (VCDSignal *cur_signal : *my_signals)
  //          {
  //              std::cout << "[" << instant <<"] : " << cur_signal->reference  <<endl;
  //              VCDBitVector * vecval;
  //              auto val = trace->get_signal_value_at(cur_signal->hash,instant);
  //              // bool okref=0;
  //              //   for(vector<Gate *>::const_iterator itrv = parseur.getCircuit()->getInputsVector()->begin();itrv!=parseur.getCircuit()->getInputsVector()->end() && !okref;itrv++)
  //              //   {
  //              //     Gate * gate = *itrv;
  //              //     string reference = cur_signal->reference;
  //              //     //cout << reference << "     " <<  gate->getName() << endl;
  //              //     if(reference == gate->getName())
  //              //     {
  //              //      //cout << "reference ok pour " << reference << endl;
  //              //      okref=1;
  //              //      cout << "vectorInput[" <<gate->getName()<<"] = "<<val -> get_value_bit() <<endl;
  //              //      if(gate->getLogicState() != val -> get_value_bit())
  //              //      {
  //              //         gate->setLogicState(val -> get_value_bit());
  //              //         gate->setDelta(1);
  //              //      }
  //              //      continue;
  //              //       //exit(1);
  //              //     }
  //              //   }
  //              bool okref=0;
  //                for(vector<Gate *>::const_iterator itrv = parseur.getCircuit()->getInputsVector()->begin();itrv!=parseur.getCircuit()->getInputsVector()->end() && !okref;itrv++)
  //                {
  //                  Gate * gate = *itrv;
  //                  string reference = cur_signal->reference;
  //                  //cout << reference << "     " <<  gate->getName() << endl;
  //                  if(reference == gate->getName())
  //                  {
  //                    okref=1;
  //                    continue;
  //                    //exit(1);
  //                  }
  //                }
  //                if(!okref)
  //                {
  //                  cout << "Ref unknown : " << cur_signal->reference << endl;
  //                  exit(1);
  //                }
  //                // Assumes val is not nullptr!
  //
  //                switch(val -> get_type()) {
  //                    case (VCD_SCALAR):
  //                        std::cout <<val -> get_value_bit(); //VCDValue::VCDBit2Char(val -> get_value_bit());
  //                        vectorStimulis.push_back(val->get_value_bit());
  //                        break;
  //                    // case (VCD_VECTOR):
  //                    //     vecval = val -> get_value_vector();
  //                    //     for(auto it = vecval -> begin();
  //                    //              it != vecval -> end();
  //                    //              ++it) {
  //                    //         std::cout << "vector"<< VCDBit2Char(*it);
  //                    //     }
  //                    //     break;
  //                    // case (VCD_REAL):
  //                    //     std::cout << "real"<< val -> get_value_real();
  //                    default:
  //                        break;
  //                }
  //           std::cout <<std::endl;
  //          }
  //          mapStimulis[instant]=vectorStimulis;
  //           i++;
  //       }
  //       map<VCDTime, vector<VCDBit> >::iterator itr;
  //       cout << "salut bg" << endl;
  //       for(itr=mapStimulis.begin();itr!=mapStimulis.end();itr++)
  //       {
  //         VCDTime time = itr->first;
  //         cout << "Time = " << time << endl;
  //         vector<VCDBit> vectorStimuliss = itr->second;
  //         for(int itrv = 0;itrv!=vectorStimuliss.size();itrv++)
  //         {
  //           cout << vectorStimuliss[itrv] << endl;
  //
  //         }
  //         // for(vector<VCDBit>::iterator itrv = vectorStimuliss.begin();itrv!=vectorStimuliss.end();itrv++)
  //         // {
  //         //   cout << vectorStimuliss[itrv] << endl;
  //         // }
  //       }
  //
  //     delete trace;
  //   }

  return 0;
}
