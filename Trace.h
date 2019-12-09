#ifndef _TRACE_H
#define _TRACE_H

#include "Chronogramme.h"

class Trace {

public:
	// Dessine dans l'image p_im
	//		un point a la position (<x>,<y>)
	//		de couleur <couleur> (gris sur 8 bits)
	// Retourne 0 si tout OK ; 1 si dessin hors de l'image
	static int dessinerPoint(Chronogramme *p_im,
					  int x, int y, unsigned char couleur);

	// Dessine dans l'image p_im
	//		une ligne d'épaisseur 1 pixel
	//		entre les points (<x1>,<y1>) et (<x2>,<y2>)
	//		de couleur <couleur> (gris sur 8 bits)
	// Retourne 0 si tout OK ; 1 si dessin hors de l'image
	static int dessinerLigne(Chronogramme *p_im,
					  int x1, int y1, int x2, int y2, unsigned char couleur);

	// Dessine dans l'image p_im
	//		un cercle de centre <x,y> d'epaisseur 1 pixel
	//		et de rayon <rayon> (ou -<rayon> si negatif)
	//		de couleur <couleur> (gris sur 8 bits)
	// Retourne 0 si tout OK ; 1 si dessin hors de l'image
	static int dessinerCercle(Chronogramme *p_im,
					   int x, int y, int rayon, unsigned char couleur);

	// Dessine dans l'image p_im
	//		un cercle plein de centre <x,y>
	//		et de rayon <rayon> (ou -<rayon> si negatif)
	//		de couleur <couleur> (gris sur 8 bits)
	// Retourne 0 si tout OK ; 1 si dessin hors de l'image
	static int dessinerCerclePlein(Chronogramme *p_im,
							int x, int y,  int rayon, unsigned char couleur);

	// Dessine dans l'image p_im
	//		un rectangle, sans rotation, d'epaisseur 1 pixel,
	//		entre les points haut gauche et bas droit
	//		(<x1>,<y1>) et (<x2>,<y2>)
	//		de couleur <couleur> (gris sur 8 bits)
	// Retourne 0 si tout OK ; 1 si dessin hors de l'image
	static int dessinerRect(Chronogramme *p_im,
					 int x1, int y1, int x2, int y2, unsigned char couleur);

	// Dessine dans l'image p_im
	//		un rectangle plein, sans rotation,
	//		entre les points haut gauche et bas droit
	//		(<x1>,<y1>) et (<x2>,<y2>)
	//		de couleur <couleur> (gris sur 8 bits)
	// Retourne 0 si tout OK ; 1 si dessin hors de l'image
	static int dessinerRectPlein(Chronogramme *p_im,
						  int x1, int y1, int x2, int y2, unsigned char couleur);

	static int DrawZero(Chronogramme *im, int x_r, int y_r);

	static int DrawOne(Chronogramme *im, int x_r, int y_r);

	static int DrawOneToZero(Chronogramme *im, int x_r, int y_r);

	static int DrawZeroToOne(Chronogramme *im, int x_r, int y_r);


private:
  // Classe utilitaire : pour interdire la construction
  // d'un objet chronogramme, on déclare un constructeur privé
  // qui n'est pas implanté
  Trace() ;

	// méthodes static utilitaires privées, utilisées par les autres méthodes
	static int putPixel(Chronogramme *p_im,
				 int x, int y, unsigned char couleur) ;

	static void swapPointsFirstLeft(int *px1, int *py1, int *px2, int *py2) ;
};

#endif
