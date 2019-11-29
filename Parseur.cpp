#include "Parseur.h"

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
    digraph = line.find("digraph");
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

  int nbline =0;
  string line;
  if(CircuitCreated)
  {
    while(getline(myfile,line))//parcourt le fichier myfile
    {
      nbline++;
      if(UselessLine(line)) continue;
      line=CleanLine(line);
      if(int(line.find('}'))>=0)
      {
        CircuitCreated = 0;
        return ;
      }
      int iin = line.find("->");
      if( iin>=0)
      { //declaration des connexinos
        string in = line.substr(0,iin);
        string out = line.substr(iin+2,line.size()-iin-3);
        if(in != "" && out !="")
        {
          if(noms.count(in) && noms.count(out))
          {
            cout << "input = " << line << "\t" << in << " se connecte à " << out << endl;
            Gate * gIn= NULL;
            Gate * gOut=NULL;
            for(std::vector<Gate*>::const_iterator it =m_circuit->getGatesVector()->begin(); it!=m_circuit->getGatesVector()->end(); ++it)
            {
              Gate * tmp = *it;
              if(tmp->getName() == in) gIn=tmp;
              if(tmp->getName() == out) gOut=tmp;
            }
            for(std::vector<Gate*>::const_iterator it =m_circuit->getInputsVector()->begin(); it!=m_circuit->getInputsVector()->end(); ++it)
            {
              Gate * tmp = *it;
              if(tmp->getName() == in) gIn=tmp;
              if(tmp->getName() == out) gOut=tmp;
            }

            if(gIn!=NULL && gOut !=NULL)
            {
              gIn->connectGate(gOut);
            }
            else
            {
              cout << "!!!    ERROR : Input or output didnt known \t in :" << in << " out : " << out << " | line = " << nbline << endl;
            }
          }
          else
          {
            cout << "!!!    ERROR : Input or output didnt known \t in :" << in << " out : " << out << " | line = " << nbline << endl;
          }
        }
        else
        {
          cout << "!!!    ERROR : input/output | line =" << nbline << endl;
          exit(1);
        }
      }//if iin>=0
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
    while(getline(myfile,line))//parcourt le fichier myfile
    {
      nbline++;
      if(UselessLine(line)) continue;

      line=CleanLine(line);
      if(int(line.find('}'))>=0)
      {
        CircuitCreated = 0;
        return ;
      }
      // cout << "CreateGates::line = " << line << endl;

      int ibracket = line.find('[');
      if( ibracket>= 0) //declaration des gates, I/O
      {
        // cout << "CreateGates::ibracket >= 0" << endl;
        // cout << "ibracket = " << ibracket << endl;
        string name=line.substr(0,ibracket);
        int ilabel=line.find("label=\"");
        int ill=line.find("\"]");
        string label="";
        if(ilabel >=0 && ill >=0) label=line.substr(ilabel+7,ill-ilabel-7);
        if (label == "" || name == "")
        {
          cout << "!!!    ERROR : label | line = " << nbline << endl;
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
          if(nbinput!=0 && !noms.count(name))
          {
            //if(typegate_vector.find(typegate)!=0)
            //cout << " Déclaration de la gate avec le nom unique " << name << " du type " << typegate <<  ", un label "<< label << " et il a " << nbinput << " inputs"<<endl;
            if(typegate == "AND")
            {
              Gate* AND = new ANDx(name, nbinput, 0);
              m_circuit->addGate(AND);
              noms.insert(name);
            }
            else if (typegate == "OR")
            {
              Gate* OR = new ANDx(name, nbinput, 0);
              m_circuit->addGate(OR);
              noms.insert(name);

            }
            else if (typegate == "NAND")
            {
              Gate* NAND = new ANDx(name, nbinput, 0);
              m_circuit->addGate(NAND);
              noms.insert(name);

            }
            else if (typegate == "NOR")
            {
              Gate* NOR = new ANDx(name, nbinput, 0);
              m_circuit->addGate(NOR);
              noms.insert(name);

            }
            else if (typegate == "XOR")
            {
              Gate* XOR = new ANDx(name, nbinput, 0);
              m_circuit->addGate(XOR);
              noms.insert(name);

            }
            // else if (typegate == "XAND")
            // {
            //   Gate* AND = new ANDx(name, 2, 0);
            //   vectorGate.push_back(AND);
            // }
            // else if (typegate == "MUX")
            // {
            //   Gate* AND = new ANDx(name, 2, 0);
            //   vectorGate.push_back(AND);
            // }
            else
            {
              cout << "!!!    ERROR : type of gate | line = " << nbline << endl;
              exit(1);
            }
          }
          else
          {
            if(nbinput!=0)   cout << "!!!    ERROR : number of inputs | line = " << nbline << endl;
            else    cout << "!!!    ERROR : name didnt known | line = " << nbline << endl;
            exit(1);
          }
          //C'est une gate
        }
        else
        {
          if(label=="INPUT")
          {
            //cout << " Déclaration de l'entree avec le nom unique " << name << ", un label "<< label <<endl;
            Gate* IN1 = new InputGate(name);
            m_circuit->addInput(IN1);
            noms.insert(name);
            // cout << "input = " << name << endl;

          }
          else if(label=="OUTPUT")
          {

           //cout << " Déclaration de la sortie avec le nom unique " << name << ", un label "<< label <<endl;
           Gate* OUT = new InputGate(name);
           m_circuit->addInput(OUT);
           noms.insert(name);

         }
          else if(label == "NOT")
          {
            //cout << " Déclaration de la gate avec le nom unique " << name << " du type NOT, un label "<< label <<endl;
            Gate* NOT = new InputGate(name);
            noms.insert(name);
            m_circuit->addGate(NOT);

          }
          else
          {
            cout << "!!!    ERROR : type | line = " << line  << endl;
            exit(1);
          }
          //C'est une I/O
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
  bool result = (line == ""  || line[1] == '%');
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
  cout << "Noms des inputs" << endl;
  for(std::vector<Gate*>::const_iterator it =f.m_circuit->getGatesVector()->begin(); it!=f.m_circuit->getGatesVector()->end(); ++it)
  {
    Gate * tmp = *it;
    out << *tmp << endl;
  }
  cout << "Noms des gates" << endl;
  for(std::vector<Gate*>::const_iterator it =f.m_circuit->getInputsVector()->begin(); it!=f.m_circuit->getInputsVector()->end(); ++it)
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
