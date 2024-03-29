#include "Parseur.h"
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <string.h>
#include <ctype.h>
using namespace std;


Parseur::Parseur(string dot_path):
m_dot_path(dot_path)
{
  cout << "file open : " << dot_path << endl;
}


void Parseur::Parser()
{
  CreateCircuit();
  CreateGates();
  CreateConnections();
}

void Parseur::CreateCircuit()
{
  ifstream myfile(getPath());
  string line;
  bool digraph_found = 0;
  int nbline =0;
  int digraph=-1;
  int tmp;
  string sdigraph;
  while(getline(myfile,line) )//parcourt le fichier myfile
  {
    nbline++;
    if(UselessLine(line)) continue;
    // cout << "allo " << endl;
    boost::to_upper(line);
    digraph = line.find("DIGRAPH");
    int acc = line.find("{");
    if(digraph >=0)
    {
      digraph_found=1;
      tmp = digraph;
      sdigraph = line.substr(tmp+8,line.size()-tmp-8 );
      if(acc >= 0)
      {
        sdigraph = line.substr(tmp+8,acc-tmp-8 );
        Circuit * circuit = new Circuit(sdigraph);
        m_circuit = circuit;
        cout << "Nom du circuit est " << m_circuit->getName()  << endl;
        CircuitCreated=1;
      }

      // cout << "maj de tmp " << digraph << "ligne lu = " << line <<  " et sdigraph = " << sdigraph << "line =" << nbline <<endl;
    }
    if(acc >=0 && digraph_found && !CircuitCreated)
    {
      // cout << "digraph found and done" << endl;
      CircuitCreated = 1;
      Circuit * circuit = new Circuit(sdigraph);
      m_circuit = circuit;
      cout << "Nom du circuit est " << m_circuit->getName()  << endl;
    }
  }//while getline
  if(!CircuitCreated)
  {
    cout << "!!! File not valid, no circuit created !!!" << endl;
    exit(1);
  }
}
void Parseur::CreateConnections()
{
  ifstream myfile(getPath());
// cout << "\t \t CreateConnections CircuitCreated = " << CircuitCreated<< endl;
  int nbline =0;
  string line;
  if(CircuitCreated)
  {
    while(getline(myfile,line) && int(line.find('}'))==-1)//parcourt le fichier myfile
    {
      nbline++;
      if(UselessLine(line)) continue;
      line=CleanLine(line);
      boost::to_upper(line);

      //cout << "ligne lue " << line << endl;
      // if(int(line.find('}'))>=0)
      // {
      //   CircuitCreated = 0;
      //   return ;
      // }
      int iin = line.find("->");
      int nbfleche =0;

      string out="";
      if( iin>=0)
      { //declaration des connexinos
        // cout << "\t \t iin >= 0 " << endl;
        string in = line.substr(0,iin);
        int ilabel = line.find("[LABEL=\"SEL\"];");
        int iCout = line.find("[LABEL=\"COUT\"];");
        //string ss = "[LABEL=\"SEL\"];";
        // cout << ss.size()  << endl<< endl;
        // cout << "\t \t ilabel = " << ilabel << endl;
        bool  sel = 0;
        int pos = 0;
        if(ilabel >= 0)
        {
          cout << "SEL detected " << endl;
          sel=1;
          out = line.substr(iin+2,line.size()-iin-2-14);
          cout << "sel out = " << out <<endl;
        }
        else
        {
           if(iCout >= 0)
          {
            cout << "COUT detected" << endl;
            pos=1;
            out = line.substr(iin+2,line.size()-iin-2-15);
            cout << "cout = " << out <<endl;
          }else{
            out = line.substr(iin+2,line.size()-iin-3);
          // cout << "out = " << out <<endl;;
          }
          

        }
          if(in != "" && out !="")
          {
            // cout << "out = " << out <<endl;
            int slt =1;
            int iinn=0;
            string in2 ="";
            string out2="";
            if((iinn = out.find("->") )>=0)
            {
              cout << "on voit 3 declarations" <<endl;
              slt =2;
              in2 = out.substr(0,iinn);
              out2 = out.substr(iinn+2,line.size()-iinn-4);
            }
            for(int cpt=0;cpt<slt;cpt++)
            {
              if(slt == 2 && cpt ==0)
              {
                cout << "on change le in/out" <<endl;
                in = in;
                out = in2;
              }
              if(noms.count(in) && noms.count(out))
              {
                // cout << "input = " << line << "\t" << in << " se connecte à " << out << endl;
                Gate * gIn= NULL;
                Gate * gOut=NULL;
                MUXx * mOut =NULL;
                bool notdonei = 1;
                bool notdoneo = 1;

                for(std::vector<Gate*>::const_iterator it =m_circuit->getGatesVector()->begin(); it!=m_circuit->getGatesVector()->end(); ++it)
                {
                  Gate * tmp = *it;
                  if(tmp->getName() == in) gIn=tmp;
                  if(tmp->getName() == out) gOut=tmp;
                }
                for(std::vector<Gate*>::const_iterator it =m_circuit->getOutputsVector()->begin(); it!=m_circuit->getOutputsVector()->end() && notdoneo; ++it)
                {
                  Gate * tmp = *it;
                  if(tmp->getName() == in)
                  {
                    gIn=tmp;
                    notdoneo = 0;
                  }
                  if(tmp->getName() == out)
                  {
                    gOut=tmp;
                    notdoneo = 0;
                  }
                }
                for(std::vector<Gate*>::const_iterator it =m_circuit->getInputsVector()->begin(); it!=m_circuit->getInputsVector()->end() && notdonei; ++it)
                {
                  Gate * tmp = *it;
                  if(tmp->getName() == in)
                  {
                    gIn=tmp;
                    notdonei = 0;
                  }
                  if(tmp->getName() == out)
                  {
                    gOut=tmp;
                    notdonei = 0;
                  }
                }
                if(sel)
                {
                  for(std::vector<MUXx*>::const_iterator it =m_circuit->getMuxVector()->begin(); it!=m_circuit->getMuxVector()->end(); ++it)
                  {
                    MUXx * tmp = *it;
                    if(tmp->getName() == out) mOut=tmp;
                  }
                }
                if(gIn!=NULL && (gOut !=NULL || mOut!=NULL))
                {
                  if(sel && mOut != NULL)
                  {
                    cout << "\t \t \t J'ai vu un MUX " << endl;
                    // MUXx(gOut)->connectSel(gIn);

                    mOut->connectSel(gIn, pos);
                    // gIn->addOutput(gOut);
                    cout << gOut << endl;
                  //   cout << "\t\t\t\t\t je push" << endl;
                   }
                   else
                   {
                     // cout << "je rentre dans le connectgate " << endl;
                     
                     cout  << "\t" << in << " se connecte à " << out << "et pos =  " << pos << endl;
                     gIn->connectGate(gOut, pos);
                    
                   }
                }
                  else
                  {
                    cout << "!!!    ERROR : Input or output didnt known \t in :" << in << " out : " << out << " | line = " << nbline << endl;
                    exit(1);
                  }
              }
              else
              {
                cout << "!!!    ERROR : Input or output didnt known \t in :" << in << " out : " << out << " | line = " << nbline << endl;
                exit(1);
              }
              in=in2;
              out=out2;
            }

          }
          else
          {
            cout << "!!!    ERROR : input/output | line =" << nbline << endl;
            exit(1);
          }

      }//if iin>=0un
    }//while getline   
  }//if CircuitCreated
}


void Parseur::CreateGates()
{
  ifstream myfile(getPath());
  int nbline=0;
  string line;
  if(CircuitCreated)
  {
    // cout << "CreateGates::CircuitCreated = 1" << endl;
    while(getline(myfile,line)&& int(line.find('}'))==-1)//parcourt le fichier myfile
    {
      nbline++;
      if(UselessLine(line)) continue;

      line=CleanLine(line);
      boost::to_upper(line);

      // if(int(line.find('}'))>=0)
      // {
      //   cout<< "\t\t\t jss mort " << endl;
      //   CircuitCreated = 0;
      //   return ;
      // }
      // cout << "CreateGates::line = " << line << endl;

      int ibracket = line.find('[');
      if( ibracket>= 0) //declaration des gates, I/O
      {
        // cout << "CreateGates::ibracket >= 0" << endl;
        // cout << "ibracket = " << ibracket << endl;
        string name=line.substr(0,ibracket);
        int ilabel=line.find("[LABEL=\"");
        int iarrow = line.find("->");
        if(iarrow > 0 && iarrow < ilabel)
        {
          cout << "slty surement un sel" << endl;
          continue; //surement un sel
        }
        int ill=line.find("\"];");
        string label="";
        if(ilabel >=0 && ill >=0) label=line.substr(ilabel+8,ill-ilabel-8);
        //boost::to_upper(label);
        else{
          cout << "Label incomplete" << endl;
          exit(1);
        }

        if (label == "" || name == "")
        {
          cout << "!!!    ERROR : label | line = " << nbline << "label = " << label << " name = " << name << endl;
          exit(1);
        }

        int cntnb =0;

        while(isdigit(label[label.size()-1-cntnb]))//check s'il y a un chiffre en fin du label + comptage
        {
          cntnb++;
        }
        int nbinput = 0;
        if(cntnb!=0)
        {

          nbinput = stoi(label.substr(label.size()-cntnb,cntnb)) ;
          string typegate = "";
          typegate = label.substr(0,label.size()-cntnb);
          // boost::to_upper(typegate);
          if(nbinput!=0 && !noms.count(name))
          {
            if(ReservedWords.count(name))
            {
              cout << "Reserved Words " << typegate << endl;
              exit(1);
            }
            //if(typegate_vector.find(typegate)!=0)
            cout << " Déclaration de la gate avec le nom unique " << name << " du type " << typegate <<  ", un label "<< label << " et il a " << nbinput << " inputs"<<endl;
            if(typegate == "AND")
            {
              Gate* AND = new ANDx(name, nbinput, 0);
              m_circuit->addGate(AND);
              noms.insert(name);
            }
            else if (typegate == "OR")
            {
              Gate* OR = new ORx(name, nbinput, 0);
              m_circuit->addGate(OR);
              noms.insert(name);

            }
            else if (typegate == "NAND")
            {
              Gate* NAND = new NANDx(name, nbinput, 0);
              m_circuit->addGate(NAND);
              noms.insert(name);

            }
            else if (typegate == "NOR")
            {
              Gate* NOR = new NORx(name, nbinput, 0);
              m_circuit->addGate(NOR);
              noms.insert(name);

            }
            else if (typegate == "XOR")
            {
              Gate* XOR = new XORx(name, nbinput, 0);
              m_circuit->addGate(XOR);
              noms.insert(name);
            }
            else if (typegate == "XNOR")
            {
              Gate* XNOR = new XNORx(name, nbinput, 0);
              m_circuit->addGate(XNOR);
              noms.insert(name);
            }
            else if (typegate == "MUX")
            {
              MUXx* MUX = new MUXx(name, nbinput, 0);
              m_circuit->addMux(MUX);
              Gate * MUXX = MUX;
              m_circuit->addGate(MUXX);
              noms.insert(name);
            }
            else
            {
              cout << "!!!    ERROR : type of gate | line = " << nbline << endl;
              exit(1);
            }
          }
          else
          {
            if(nbinput!=0)   cout << "!!!    ERROR : number of inputs | line = " << nbline << endl;
            else    cout << "!!!    ERROR : name arleady known | line = " << nbline << " name = "<< name<< endl;
            exit(1);
          }
          //C'est une gate
        }
        else
        {
          if(!noms.count(name) && !ReservedWords.count(name))
          {
          if(label=="INPUT")
          {
            cout << " Déclaration de l'entree avec le nom unique " << name << ", un label "<< label <<endl;
            Gate* IN1 = new InputGate(name);
            m_circuit->addInput(IN1);
            noms.insert(name);
            // cout << "input = " << name << endl;

          }
          else if(label=="OUTPUT")
          {

           cout << " Déclaration de la sortie avec le nom unique " << name << ", un label "<< label <<endl;
            Gate* OUT = new OutputGate(name);
            m_circuit->addOutput(OUT);
           noms.insert(name);

         }
          else if(label == "NOT")
          {
            cout << " Déclaration de la gate avec le nom unique " << name << " du type NOT, un label "<< label <<endl;
            Gate* NOT = new NOTx(name);
            noms.insert(name);
            m_circuit->addGate(NOT);

          }
          else if(label == "FA")
          {
            cout << " Déclaration de la gate avec le nom unique " << name << " du type FA, un label "<< label <<endl;
            Gate* FAx = new FA(name); //constructeur (nom, logicState)
            noms.insert(name);
            m_circuit->addGate(FAx);

          }
          else
          {
            cout << "!!!    ERROR : type | line = " << line <<"   "<<name <<"   "<< label << endl;
            exit(1);
          }
          //C'est une I/O
        }
        else
        {
          cout << "!!!    ERROR : name arleady known or is a reserved words | line = " << nbline << " name = "<< name<< endl;
          exit(1);
        }
        }
      }//if ibracket>=0
    }//while getline
  }//if CircuitCreated
}


string Parseur::CleanLine(string line)
{
  if(int ind_pv=line.find(";"))
  {
    line.substr(0,ind_pv);
  }
  string newLine;
  for (size_t i = 0; i < line.length(); i++) {
      if (line[i] != ' ') {
          newLine += line[i];
      }
  }
  return newLine;
}

bool Parseur::UselessLine(string line)
{
  bool result = (line == ""  || line[0] == '%');
  // cout << "UselessLine::line = " << line<< " result = " << result <<  endl;
  return(result);//detect empty lines or commented ones
}

ostream& operator <<(ostream& out, const  Parseur &f)
{
  // cout << "Noms dans le fichier "<< endl;
  // for(std::set<string>::iterator it =f.noms.begin(); it!=f.noms.end(); ++it)
  // {
  //   out << *it << endl;
  // }
  cout << "Noms des gates" << endl;
  for(std::vector<Gate*>::const_iterator it =f.m_circuit->getGatesVector()->begin(); it!=f.m_circuit->getGatesVector()->end(); ++it)
  {
    Gate * tmp = *it;
    out << *tmp << endl;
  }
  cout << "Noms des inputs" << endl;
  for(std::vector<Gate*>::const_iterator it =f.m_circuit->getInputsVector()->begin(); it!=f.m_circuit->getInputsVector()->end(); ++it)
  {
    Gate * tmp = *it;
    out << *tmp << endl;
  }
  cout << "Noms des outputs" << endl;
  for(std::vector<Gate*>::const_iterator it =f.m_circuit->getOutputsVector()->begin(); it!=f.m_circuit->getOutputsVector()->end(); ++it)
  {
    Gate * tmp = *it;
    out << *tmp << endl;
  }
  // out << "" << f << "" << f<< endl;
  return out;
}


string Parseur::getPath()
{
//  cout << "getPath " << m_dot_path <<endl;
  return m_dot_path;
}
void Parseur::setPath(string dot_path)
{
  m_dot_path = dot_path;
}