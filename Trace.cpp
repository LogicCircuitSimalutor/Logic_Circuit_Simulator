#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "Trace.h"

// tentative de travail avec la SDL ; sans succès
// http://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom

//------------
// Utilitaires
//------------

int Trace::putPixel(Chronogramme *p_im,
			 int x, int y, unsigned char couleur) {
	if(x<0 || y < 0 || x > p_im->getNbl()-1 || y > p_im->getNbc()-1) {
		return 1;
	}
	p_im->setPixel(x, y, couleur);
	return 0;
}

void Trace::swapPointsFirstLeft(int *px1, int *py1, int *px2, int *py2) {
	if(*px1 > *px2) {
		int tmp;
		tmp=*px1;
		*px1=*px2;
		*px2=tmp;
		tmp=*py1;
		*py1=*py2;
		*py2=tmp;
	}
}

//------------

int Trace::dessinerPoint(Chronogramme *p_im,
				  int x, int y, unsigned char couleur){
	int errorDraw = 0;
	errorDraw |= Trace::Trace::putPixel(p_im, x, y, couleur);
	return errorDraw;
}



//int Trace::putLigne_V(unsigned char *pixels, int nbl, int nbc,
//			   int x1, int x2, int y,
//			   unsigned char couleur){
//	int i;
//	int errorDraw = 0;
//	int xmin = min(x1, x2);
//	int xmax = max(x1, x2);
//	for(int i=xmin; i<=xmax; i++) {
//		errorDraw |= Trace::putPixel(p_im, i, y, couleur);
//	}
//	if(errorDraw) {
//		fprintf(stderr, "Dessin hors de l'image détecté...\n");
//	}
//}
//
//int Trace::putLigne_H(unsigned char *pixels, int nbl, int nbc,
//			   int x, int y1, int y2,
//			   unsigned char couleur){
//	int i;
//	int errorDraw = 0;
//	int ymin = min(y1, y2);
//	int ymax = max(y1, y2);
//	for(int i=ymin; i<=ymax; i++) {
//		errorDraw |= Trace::putPixel(p_im, x, i, couleur);
//	}
//	return errorDraw;
//}
//

//int Trace::dessinerLigne(unsigned char *pixels, int nbl, int nbc,
//				  int x1, int y1, int x2, int y2,
//				  unsigned char couleur){
//int errorDraw = 0;
//
//	if(x1==x2) {
//		errorDraw |= putLigne_H(p_im, x1, y1, y2, couleur);
//		if(errorDraw) {
//			fprintf(stderr, "Dessin hors de l'image détecté...\n");
//		}
//	}
//
//	if(y1==y2) {
//		errorDraw |= putLigne_V(p_im, x1, x2, y1, couleur);
//		if(errorDraw) {
//			fprintf(stderr, "Dessin hors de l'image détecté...\n");
//		}
//	}
//	Trace::swapPointsFirstLeft(&x1, &y1, &x2, &y2);
//	int x,y;
//	int first = 1;
//	x=x1;
//	y=y1+(( (float) (y2-y1)/(x2-x1))*(x-x1)); //y is the same precentage of trip x made on its trip
//	errorDraw |= Trace::putPixel(p_im, x, y, couleur);
//
//	int yold = y;
//	for(x=x1+1; x<=x2; x++) //we follow x coord. one-by-one
//	{
//		y=y1+(( (float) (y2-y1)/(x2-x1))*(x-x1)); //y is the same precentage of trip x made on its trip
//		errorDraw |= putLigne_H(p_im, x, yold, y, couleur);
//		yold = y;
//	}
//	if(errorDraw) {
//		fprintf(stderr, "Dessin hors de l'image détecté...\n");
//	}
//	return errorDraw;
//}

int Trace::dessinerLigne(Chronogramme *p_im,
				  int x1, int y1, int x2, int y2,
				  unsigned char couleur){
	int errorDraw = 0;
	int i;
	double x = x2 - x1;
	double y = y2 - y1;
	double length = sqrt( x*x + y*y );
	double addx = x / length;
	double addy = y / length;
	x = x1;
	y = y1;

	for ( i = 0; i < length; i += 1) {
		errorDraw |= Trace::putPixel(p_im, x, y, couleur);
		x += addx;
		y += addy;
	}
	return errorDraw;
}


int Trace::dessinerCercle(Chronogramme *p_im,
				   int x0, int y0, int radius, unsigned char c){
	int errorDraw = 0;

	if(radius < 0) radius = -radius;

	int x = radius, y = 0;
	int radiusError = 1-x;

	while(x >= y)
	{
		errorDraw |= Trace::putPixel(p_im, x + x0, y + y0, c);
		errorDraw |= Trace::putPixel(p_im, x + x0, -y + y0, c );

		errorDraw |= Trace::putPixel(p_im, y + x0, x + y0, c);
		errorDraw |= Trace::putPixel(p_im, y + x0, -x + y0, c);

		errorDraw |= Trace::putPixel(p_im, -x + x0, y + y0, c);
		errorDraw |= Trace::putPixel(p_im, -x + x0, -y + y0, c);

		errorDraw |= Trace::putPixel(p_im, -y + x0, x + y0, c);
		errorDraw |= Trace::putPixel(p_im, -y + x0, -x + y0, c);

		y++;
        if(radiusError<0)
			radiusError+=2*y+1;
        else
        {
			x--;
			radiusError+=2*(y-x+1);
        }
	}
	return errorDraw;
}

int Trace::dessinerCerclePlein(Chronogramme *p_im,
						int x0, int y0, int radius, unsigned char c){
	int errorDraw = 0;

	int x = radius, y = 0;
	int radiusError = 1-x;

	while(x >= y)
	{
		//		errorDraw |= putLigne_H(p_im,
		//								x + x0, y + y0, -y + y0, c);
		//		errorDraw |= putLigne_H(p_im,
		//								y + x0, x + y0, -x + y0, c);
		//		errorDraw |= putLigne_H(p_im,
		//								-x + x0, y + y0, -y + y0, c);
		//		errorDraw |= putLigne_H(p_im,
		//								-y + x0, x + y0, -x + y0, c);

		errorDraw |= dessinerLigne(p_im,
								   x + x0, y + y0, x + x0, -y + y0, c);
		errorDraw |= dessinerLigne(p_im,
								   y + x0, x + y0, y + x0, -x + y0, c);
		errorDraw |= dessinerLigne(p_im,
								   -x + x0, y + y0, -x + x0, -y + y0, c);
		errorDraw |= dessinerLigne(p_im,
								   -y + x0, x + y0, -y + x0, -x + y0, c);

		y++;
        if(radiusError<0)
			radiusError+=2*y+1;
        else
        {
			x--;
			radiusError+=2*(y-x+1);
        }
	}
	return errorDraw;
}

int Trace::dessinerRect(Chronogramme *p_im,
				 int x1, int y1, int x2, int y2, unsigned char c){
	int errorDraw = 0;
	//	errorDraw |= putLigne_H(p_im,
	//							x1, y1, y2, c);
	//	errorDraw |= putLigne_H(p_im,
	//							x2, y1, y2, c);
	//	errorDraw |= putLigne_V(p_im,
	//							x1, x2, y1, c);
	//	errorDraw |= putLigne_V(p_im,
	//							x1, x2, y2, c);

	errorDraw |= dessinerLigne(p_im,
							   x1, y1, x1, y2, c);
	errorDraw |= dessinerLigne(p_im,
							   x2, y1, x2, y2, c);
	errorDraw |= dessinerLigne(p_im,
							   x1, y1, x2, y1, c);
	errorDraw |= dessinerLigne(p_im,
							   x1, y2, x2, y2, c);
	return errorDraw;
}

int Trace::dessinerRectPlein(Chronogramme *p_im,
					  int x1, int y1, int x2, int y2, unsigned char c){
	Trace::swapPointsFirstLeft(&x1, &y1, &x2, &y2);
	int errorDraw = 0;
	int x;
	for(x=x1;x<=x2;x++) {
		errorDraw |= dessinerLigne(p_im,
								   x, y1, x, y2, c);
		//		errorDraw |= putLigne_H(p_im,
		//								x, y1, y2, c);
	}
	return errorDraw;
}

int Trace::DrawZero(Chronogramme *im, int x_r, int y_r){
	int errorDraw = 0;
	int factor = 2;
	errorDraw |= Trace::dessinerLigne(im, x_r-20, y_r, x_r-20, y_r+factor*20, 0);
	errorDraw |= Trace::dessinerLigne(im, x_r-21, y_r, x_r-21, y_r+factor*20, 0);
	return errorDraw;
}

int Trace::DrawOne(Chronogramme *im, int x_r, int y_r){
	int errorDraw = 0;
	int factor = 2;
	errorDraw |= Trace::dessinerLigne(im, x_r-20, y_r, x_r-20, y_r+factor*20, 0);
	errorDraw |= Trace::dessinerLigne(im, x_r-19, y_r, x_r-19, y_r+factor*20, 0);
	return errorDraw;
}

int Trace::DrawZeroToOne(Chronogramme *im, int x_r, int y_r){
	int errorDraw = 0;
	int factor = 2;
	errorDraw |= Trace::dessinerLigne(im, x_r-20, y_r, x_r, y_r, 0); //ligne verticale
	errorDraw |= Trace::dessinerLigne(im, x_r-20, y_r-1, x_r, y_r-1, 0); //ligne verticale

	errorDraw |= Trace::dessinerLigne(im, x_r-20, y_r, x_r-20, y_r+factor*20, 0); //horizontale
	errorDraw |= Trace::dessinerLigne(im, x_r-19, y_r, x_r-19, y_r+factor*20, 0); //horizontale
	return errorDraw;
}

int Trace::DrawOneToZero(Chronogramme *im, int x_r, int y_r){
	int errorDraw = 0;
	int factor = 2;
	Trace::dessinerLigne(im, x_r-20, y_r, x_r, y_r, 0); //ligne verticale
	Trace::dessinerLigne(im, x_r-20, y_r-1, x_r, y_r-1, 0); //ligne verticale

	Trace::dessinerLigne(im, x_r, y_r, x_r, y_r+factor*20, 0); //horizontale
	Trace::dessinerLigne(im, x_r-1, y_r, x_r-1, y_r+factor*20, 0); //horizontale
	return errorDraw;
}