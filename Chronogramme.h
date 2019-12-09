#ifndef _CHRONOGRAMME_H_
#define _CHRONOGRAMME_H_


#include <iostream>
#include <vector>
#include "Gate.h"
#include "Signal.h"
using namespace std;

class Chronogramme {

// Membres privés
private:
    // Attributs
    int nblignes, nbcolonnes;
    unsigned char * data;
    std::vector<Signal *> m_signal;

    // Methodes privees

    // Alloue le tableau data de taille nl*nc et affecte nblignes et nbcolonnes
    // si nl ou nc sont <= 0, n'alloue rien et marque *this comme invalide.
    void allouer(int nl, int nc) ;

    // si isValid(), copie le tableau de pixel src dans this->data
    // PRECONDITION : data est un tableau de taille nblignes*nbcolonnes
    void copierTabPixel(unsigned char* data);


// Interface publique
public:
    /////////////////////////////
    // Gestion du cycle de vie
    // Constructeurs, destructeur, opérateur d'affectation
    /////////////////////////////

    // Construit une image sans pixel, invalide, si nbl ou nbc <=0
    // ou de taille nbl/nbc et noire sinon
    Chronogramme(int nbl=0, int nbc=0) ;
    // Construit une image sans pixel, invalide, si nbl ou nbc <=0
    // ou de taille nbl/nbc et noire sinon
    Chronogramme(int nbl, int nbc, unsigned char valeurpix) ;
    // Constructeur de copie
    Chronogramme(const Chronogramme & other) ;

    // Destructeur
    ~Chronogramme() ;

    // Opérateur d'affectation
    Chronogramme& operator=(const Chronogramme& other);


    /////////////////////////////
    // Accesseurs et modifieurs de base
    /////////////////////////////

    // Retourne true si l'objet *this est valide.
    // un image est valide si le pointeur sur le tableau de pixels est non NULL (alloué) ;
    // c'est à dire d'ailleurs si le nombre de ligne et de colonnes de l'image est non nul.
    bool isValid() const {
        return data != NULL;
    }
    int getNbl() const  {
        return nblignes;
    }
    int getNbc() const {
        return nbcolonnes;
    }

    int getNbSignal() const{
        return m_signal.size();
    }

    const vector <Signal * >* getSignalVector() const{
        return &m_signal;
    }

    vector <Signal * >* getSignalVector(){
        return &m_signal;
    }

    bool addSignal(Signal* s);
    // accesseur sur pixel. Retourne la valeur du pixel (i,j)
    // PRECONDITION : le pixel (i,j) existe dans l'image *this
    unsigned char getPixel(int i, int j) const {
        return (data+nbcolonnes*i)[j];
    }

    // modifieur de pixel. Mofifie la valeur du pixel (i,j)
    // PRECONDITION : le pixel (i,j) existe dans l'image *this
    void setPixel(int i, int j, unsigned char c) {
        (data+nbcolonnes*i)[j] = c;
    }



    /////////////////////////////
    // Opérateurs travaillant sur le tableau de pixel
    /////////////////////////////

    // CHOISIR entre l'opérater [](int) qui retourne un ptr sur ligne
    // et l'opérateur ()(int, int) qui retourne un pixel !

    // operateur crochet non const
    // PRECONDITION : la ligne lig existe dans l'image *this
    unsigned char* operator[]( int lig);

    // version const de l'perateur crochet
    // PRECONDITION : la ligne lig existe dans l'image *this
    // Cette version const est utile pour pouvoir travailler
    // avec des images constantes, eg passées en param const
    // à une fonction.
    // Par exemple, si im est déclarée const
    //			const Chronogramme im
    // sans cette verson const, il est interdit d'écrire cout << im[i][j] ;
    const unsigned char* operator[](int lig) const ;


//	// operateur (i,j) non const
//	// PRECONDITION : i et j doivent etre valides
//	unsigned char & operator()(int i, int j);
//
//	// version const de l'perateur (i,j)
//	// PRECONDITION : i et j doivent etre valides
//	// Cette version const est utile pour pouvoir travailler avec des images constantes.
//	// Par exemple, si im est déclarée const
//	//			const Chronogramme im
//	// sans cette version const, il est interdit d'écrire im(i,j)
//	unsigned char operator()(int i, int j) const ;

    // Operator++ prefixe
    Chronogramme& operator++() ;

    // Operator++ postfixe
    Chronogramme operator++(int) ;


    /////////////////////////////
    // E/S fichier
    /////////////////////////////

    // Lecture d'un fichier image.
    // En cas d'erreur de chargement, l'image *this n'est pas modifiee
    // Retourne 0 si OK, un nb non nul si erreur
    int charger(const char * nomFichier);

    // Sauvegarde dans un fichier image.
    // Retourne 0 si OK, un nb non nul si erreur
    int sauver(const char * nomFichier) const;

    // Réalise un fondu entre l'image *this et l'image im en nb étapes
    // Les nb images intermédiaires seront sauvées
    // dans des fichiers nommés <racineNomFichier>_001 à <racineNomFichier>_00<nb>
    // Si im n'a pas la meme taille que *this, rien n'est fait
    void sauverFondu(const Chronogramme& im, int nb , const char* racineNomFichier) const;

    void TraceChronogramme(int clk);

    void TraceClock(int NbPeriod, int x, int y);

    void TraceNewSignalLine(int x, int y);

    /////////////////////////////
    // Fonctions amies
    /////////////////////////////

    // retourne vrai si les images sont identiques (au pixel prêt)
    friend bool operator==(const Chronogramme& im1 , const Chronogramme& im2);

    // Retourne une nouvelle image dont tous les pixels ont été mutiplités d'un facteur k
    friend Chronogramme operator*(const Chronogramme& im, double k);

    // Retourne une nouvelle image
    // dont les pixels sont l'addition deux à deux des pixels des images im1 et im2
    // Si les image im1 ou im2 n'ont pas la même taille, l'image retournée est invalide.
    friend Chronogramme operator+(const Chronogramme & im1, const Chronogramme & im2);

    friend ostream& operator<<(ostream& out, const Chronogramme& a);
};

#endif
