#include "Parseur.h"
#include "ParseurVCD.h"
using namespace std;


ParseurVCD::ParseurVCD(string vcd_path):
m_vcd_path(vcd_path)
{
  cout << "file open : " << vcd_path << endl;
  VCDFileParser parser;
  m_parser = parser;
  VCDFile *trace = parser.parse_file(vcd_path);
  m_trace=trace;
}


void ParseurVCD::Parser( map<int, vector<bool> > & mapStimulis)
{
  VCDFile *trace = m_trace;
    if (trace)
    {
        // std::cout << "Parse successful." << std::endl;
        // std::cout << "Version:       " << trace->version << std::endl;
        // std::cout << "Date:          " << trace->date << std::endl;
        // std::cout << "Signal count:  " << trace->get_signals()->size() << std::endl;
        // std::cout << "Times Recorded:" << trace->get_timestamps()->size() << std::endl;
        if (trace->get_signals()->size() == m_circuit->getInputsVector()->size())
        {
            // std::cout << " [" << signal->size << ":0]";
        }
        else
        {
          cout << "VCD file dont have the same number of inputs that the DOT file" << endl;
          cout << "Number of inputs on VCD = " << trace->get_signals()->size() << "\n"
          <<"Number of inputs on DOT = " << m_circuit->getInputsVector()->size() <<endl;
          exit(1);
        }

        // Print out every signal in every scope.
        // for (VCDScope *scope : *trace->get_scopes())
        // {
        //
        //     // std::cout << "Scope: " << scope->name << std::endl;
        //
        //     // for (VCDSignal *signal : scope->signals)
        //     // {
        //     //
        //     //
        //     //   //vectorInput=Parseur.getvectorInput();
        //     //   //if(signal->reference != )
        //     //     // std::cout << "\t" << signal->hash << "\t"  << signal->reference;
        //     //
        //     //
        //     //
        //     //
        //     //     //std::cout << std::endl;
        //     // }
        //   }
        //   //std::cout << "Looking for signals" <<std::endl;
          auto my_signals =  trace->get_signals();
        //   //std::cout << "Looking for timestamps" <<std::endl;
        auto  my_timestamps = trace->get_timestamps();
        int i=0;
        for (VCDTime instant : *my_timestamps)
          {
            vectorStimulis.clear();
            const int time = int(instant);
            cout << "ottotot" << time << instant << endl;
            for (VCDSignal *cur_signal : *my_signals)
             {
                 //std::cout << "[" << instant <<"] : " << cur_signal->reference  <<endl;
                 // VCDBitVector * vecval;
                 auto val = trace->get_signal_value_at(cur_signal->hash,instant);
                 // bool okref=0;
                 //   for(vector<Gate *>::const_iterator itrv = parseur.getCircuit()->getInputsVector()->begin();itrv!=parseur.getCircuit()->getInputsVector()->end() && !okref;itrv++)
                 //   {
                 //     Gate * gate = *itrv;
                 //     string reference = cur_signal->reference;
                 //     //cout << reference << "     " <<  gate->getName() << endl;
                 //     if(reference == gate->getName())
                 //     {
                 //      //cout << "reference ok pour " << reference << endl;
                 //      okref=1;
                 //      cout << "vectorInput[" <<gate->getName()<<"] = "<<val -> get_value_bit() <<endl;
                 //      if(gate->getLogicState() != val -> get_value_bit())
                 //      {
                 //         gate->setLogicState(val -> get_value_bit());
                 //         gate->setDelta(1);
                 //      }
                 //      continue;
                 //       //exit(1);
                 //     }
                 //   }
                 bool okref=0;
                   for(vector<Gate *>::const_iterator itrv = m_circuit->getInputsVector()->begin();itrv!=m_circuit->getInputsVector()->end() && !okref;itrv++)
                   {
                     Gate * gate = *itrv;
                     string reference = cur_signal->reference;
                     //cout << reference << "     " <<  gate->getName() << endl;
                     if(reference == gate->getName())
                     {
                       okref=1;
                       continue;
                       //exit(1);
                     }
                   }
                   if(!okref)
                   {
                     cout << "Ref unknown : " << cur_signal->reference << endl;
                     exit(1);
                   }
                   // Assumes val is not nullptr!

                   switch(val -> get_type()) {
                       case (VCD_SCALAR):
                           //std::cout <<val -> get_value_bit(); //VCDValue::VCDBit2Char(val -> get_value_bit());
                           bool bvalue;
                           bvalue =0;
                           if(val->get_value_bit() == 1)
                           {
                             bvalue =1;
                           }
                           vectorStimulis.push_back(bvalue);
                           break;
                       // case (VCD_VECTOR):
                  // mapStimulis     //     vecval = val -> get_value_vector();
                       //     for(auto it = vecval -> begin();
                       //              it != vecval -> end();
                       //              ++it) {
                       //         std::cout << "vector"<< VCDBit2Char(*it);
                       //     }
                       //     break;
                       // case (VCD_REAL):
                       //     std::cout << "real"<< val -> get_value_real();
                       default:
                           break;
                   }
              //std::cout <<std::endl;
             }
             mapStimulis[time]=vectorStimulis;
              i++;
          }


        delete trace;
      }
}
void ParseurVCD::connectCircuit(Circuit * circuit)
 {
   m_circuit = circuit;
    cout << m_circuit <<endl;
   cout << circuit;
   // circuit->print();
   // cout << "circuit ====================== " <<  m_circuit.print() << *circuit << endl;
 }
string ParseurVCD::getPath()
{
//  cout << "getPath " << m_dot_path <<endl;
  return m_vcd_path;
}
void ParseurVCD::setPath(string vcd_path)
{
  m_vcd_path = vcd_path;
}

ostream& operator <<(ostream& out, const  ParseurVCD &f)
{
  out << "\t\t==== Stimulis ====" << endl;
  // for(map<VCDTime, vector<VCDBit> >::const_iterator itr = f.mapStimulis.begin();itr!=f.mapStimulis.end();itr++)
  // {
  //   VCDTime time = itr->first;
  //   out << "Time = " << time << endl;
  //   vector<VCDBit> vectorStimuliss = itr->second;
  //   for(int itrv = 0;itrv!=vectorStimuliss.size();itrv++)
  //   {
  //     out << vectorStimuliss[itrv] << endl;
  //   }
  // }
  return out;
}
