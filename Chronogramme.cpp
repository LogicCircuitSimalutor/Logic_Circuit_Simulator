#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdio.h>


using namespace std;

#include "Chronogramme.h"
#include "BmpIO.h"
#include "Trace.h"


// Methodes privees

void Chronogramme::allouer(int nl, int nc) {
    if (nl>0 && nc>0) {
        nblignes= nl;
        nbcolonnes= nc;
        data = new unsigned char[nblignes*nbcolonnes];
    }
    else {
        nblignes= 0;
        nbcolonnes= 0;
        data=NULL;
    }
}


void Chronogramme::copierTabPixel(unsigned char* data) {
    if(isValid()) {
        memcpy(this->data, data, nblignes*nbcolonnes*sizeof(*data));
    }
}

// Interface publique

/////////////////////////////
// Gestion du cycle de vie
// Constructeurs, destructeur, opérateur d'affectation
/////////////////////////////

Chronogramme::Chronogramme(int nl, int nc):
    nblignes(0), nbcolonnes(0), data(NULL) {
    if (nl>0 && nc>0) {
        allouer(nl, nc);
        for(int i = 0 ; i < nblignes * nbcolonnes ; i ++) {
            data[i] = 0;
        }
    }
}

Chronogramme::Chronogramme(int nl, int nc, unsigned char val):
    nblignes(0), nbcolonnes(0), data(NULL) {
    if (nl>0 && nc>0) {
        allouer(nl, nc);
        for(int i = 0 ; i < nblignes * nbcolonnes ; i ++) {
            data[i] = val;
        }
    }
}

Chronogramme::Chronogramme(const Chronogramme& src):
    nblignes(0), nbcolonnes(0), data(NULL) {
    if (src.isValid()) {
        allouer(src.nblignes, src.getNbc());
        //this->copierTabPixel(src.data);
        for(int i = 0 ; i < nblignes * nbcolonnes ; i ++) {
            this->data[i] = src.data[i];
        }
    }
}

Chronogramme::~Chronogramme() {
    delete [] data; // OK si data == NULL
}


Chronogramme& Chronogramme::operator=(const Chronogramme& src) {
    cout << "Operator d'affection de "<<this << endl;
    // Attention si this et src sont le meme objet,
    // c'est idiot et on ne fait rien
    // (gestion du "self assignment")
    if (this==&src) return *this;

    // Liberation si this est deja alloue sauf si dimensions identiques
    delete [] data;

    nblignes = nbcolonnes = 0;
    data = NULL;


    if (src.isValid()) { // ou if(src.data != NULL)
        allouer(src.nblignes,src.nbcolonnes);
        //copierTabPixel(src.data);
        for(int i = 0 ; i < nblignes * nbcolonnes ; i ++) {
            this->data[i] = src.data[i];
        }
    }
    return *this;
}


/////////////////////////////
// Opérateurs travaillant sur le tableau de pixel
/////////////////////////////

unsigned char* Chronogramme::operator[](int i ) {
    return data+nbcolonnes*i;
}

const unsigned char* Chronogramme::operator[](int i ) const {
    return data+nbcolonnes*i;
}

//unsigned char& Chronogramme::operator()(int i, int j ) {
//	return *(data+nbcolonnes*i + j);
//}
//
//unsigned char Chronogramme::operator()(int i, int j ) const {
//	return *(data+nbcolonnes*i + j);
//}


Chronogramme& Chronogramme::operator++() {
    for (int i=0; i<nblignes*nbcolonnes; i++)
        data[i]++;
    return *this;
}

Chronogramme Chronogramme::operator++(int a) {
    Chronogramme tmp(*this);
    // On utilise l'operateur ++ prefixe pour ne pas reecrire
    ++(*this);
    return tmp;
}



/////////////////////////////
// Fonctions amies
/////////////////////////////

bool operator==(const Chronogramme& a, const Chronogramme& b) {
    if(  a.data == NULL && b.data == NULL) {
        return true;
    }
    return(a.data && b.data && (a.nblignes==b.nblignes) && a.nbcolonnes==b.nbcolonnes
           && !memcmp(a.data,b.data,a.nblignes*a.nbcolonnes*sizeof(*(a.data))));
}

Chronogramme operator*(const Chronogramme& a, double k) {
    Chronogramme tmp(a);
    for (int i=0; i<a.nblignes*a.nbcolonnes; i++) tmp.data[i] *=k;
    return tmp;
}

Chronogramme operator+(const Chronogramme& a, const Chronogramme& b) {
    if (a.nblignes!=b.nblignes || a.nblignes!=b.nblignes) return Chronogramme();
    Chronogramme tmp(a);
    // Efficace mais implementation dependant
    for (int i=0; i<a.nblignes*a.nbcolonnes; i++) tmp.data[i] += b.data[i] ;
    // Version plus propre, moins efficace
    /*
     for (int i=0; i<a.nblignes; i++)
     for(int j=0; j<a.nbcolonnes; j++)
     tmp[i][j] += b[i][j];
     */
    return tmp;
}





ostream& operator<<(ostream& out, const Chronogramme& a) {
    out << "Order of signals for chronogramme : " << endl;
    vector <Signal * >::const_iterator itr = a.m_signal.begin();
    while(itr != a.m_signal.end()){
        Signal * tmp = *itr;
        out << tmp->getAddrGate()->getName() << "\n" << endl;
        itr++;
    }
    return out;
}



/////////////////////////////
// E/S fichier
/////////////////////////////

int Chronogramme::charger(const char* fic) {
    int nl, nc;
    if(BmpIO::readsizebmpgray(fic, &nl, &nc) != 0) {
        cout << "Pb lecture " << endl;
        return 1;
    }

    allouer(nl,nc);
    if(BmpIO::readpixelsbmpgray(fic, data, nl*nc) != 0) {
        cout << "Pb lecture 2" << endl;
        return 1;
    }
    return 0;
}


int Chronogramme::sauver(const char* fic) const {
    return BmpIO::savebmpgray(fic,data,nblignes,nbcolonnes);
}


void Chronogramme::sauverFondu(const Chronogramme& im, int nb, const char* racineNomFichier) const {
    if(im.nblignes != im.nbcolonnes || im.nbcolonnes != im.nblignes) {
        return;
    }
    Chronogramme tmp(*this);
    char ss[512];
    for (int i=0; i<nb; i++) {
        tmp = *this*((double)i/nb)+im*((nb-(double)i)/nb);
        sprintf(ss,"%s%03d.bmp", racineNomFichier, i);
        tmp.sauver(ss);
    }
}

bool Chronogramme::addSignal(Signal* s){
    m_signal.push_back(s);
    return true;
}

void Chronogramme::TraceClock(int NbPeriod, int x, int y){
    Trace::dessinerLigne(this, 10, 20, 50, 20, 0); //ligne verticale
    Trace::dessinerLigne(this, 50, 20, 50, 980, 0); //ligne horizontale
    int factor = 2;
    for(int i = 0 ; i < NbPeriod+1 ; i++){
        //On trace une impulsion de CLK
        Trace::dessinerLigne(this, x, y, x, y+factor*10, 0);
        Trace::dessinerLigne(this, x-1, y, x-1, y+factor*10, 0);

        Trace::dessinerLigne(this, x-20, y+factor*10, x-20, y+factor*20, 0);
        Trace::dessinerLigne(this, x-19, y+factor*10, x-19, y+factor*20, 0); //double épaisseur

        Trace::dessinerLigne(this, x-20, y+factor*10, x, y+factor*10, 0); //ligne verticale
        Trace::dessinerLigne(this, x-20, y+factor*11, x, y+factor*10+1, 0); //ligne verticale

        Trace::dessinerLigne(this, x-20, y+factor*20, x, y+factor*20, 0); //ligne verticale y+20
        Trace::dessinerLigne(this, x-20, y+factor*20-1, x, y+factor*20-1, 0); //ligne verticale y+20

        y+=factor*20;

        if(i == NbPeriod){
        Trace::dessinerLigne(this, x, y, x, y+factor*10, 0);
        Trace::dessinerLigne(this, x-1, y, x-1, y+factor*10, 0);
        }
    }

}

void Chronogramme::TraceNewSignalLine(int x, int y){
    int size = m_signal.size();

    for(int i = 0 ; i < size ; i++){
        //ajout d'un signal
        Trace::dessinerLigne(this, x, y, x+40, y, 0); //ligne verticale
        Trace::dessinerLigne(this, x+40, 20, x+40, 980, 0); //ligne horizontale
        x+=40;
    }

}

void Chronogramme::TraceChronogramme(int clk){
    vector<Signal *>::const_iterator itr_signal = getSignalVector()->begin();
    int factor = 2;
    /*>CLK is null, first value of output, init of chrono*/
    if(!clk){
        while(itr_signal != getSignalVector()->end()){
            Signal * tmp_signal = *itr_signal;
            Gate* tmp_gate = tmp_signal->getAddrGate();
            //We call the trace function in function of logic state of tmp_gate
            if(tmp_gate->getLogicState()){
                Trace::DrawZeroToOne(this, tmp_signal->getX(), tmp_signal->getY()+1);
            }else{
                Trace::DrawZero(this, tmp_signal->getX()+20, tmp_signal->getY()+1);
            }
            tmp_signal->setY(tmp_signal->getY()+factor*20);
            tmp_signal->setPrevLogicState(tmp_gate->getLogicState());
            itr_signal++;
        }
    }else{
        itr_signal = getSignalVector()->begin();
        while(itr_signal != getSignalVector()->end()){
            Signal * tmp_signal = *itr_signal;
            Gate* tmp_gate = tmp_signal->getAddrGate();
            
            if(tmp_gate->getLogicState()){
                if(tmp_signal->getPrevLogicState()){
                    Trace::DrawOne(this, tmp_signal->getX(), tmp_signal->getY()+1);
                }else{
                    Trace::DrawZeroToOne(this, tmp_signal->getX(), tmp_signal->getY()+1);
                }
            }else{
                if(!(tmp_signal->getPrevLogicState())){
                   Trace::DrawZero(this, tmp_signal->getX()+20, tmp_signal->getY()+1);
                }else{
                   Trace::DrawOneToZero(this, tmp_signal->getX(), tmp_signal->getY()+1);
                }
            }
            tmp_signal->setPrevLogicState(tmp_gate->getLogicState());
            tmp_signal->setY(tmp_signal->getY()+factor*20);
            itr_signal++;
        }

    }

}