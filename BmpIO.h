#ifndef _BMP_IO_H
#define _BMP_IO_H


// Input / output d'images au format BMP
// CLasse dite "utilitaire" : uniquement des méthodes statiques
// Permet de réaliser des entrées - sorties d'images depuis/vers
// des fichiers au format BMP
class BmpIO {
private:
  // Classe utilitaire : pour interdire la construction
  // d'un objet BmpIO, on déclare un constructeur privé
  // qui n'est pas implanté
  BmpIO() ;

public:
  // Sauve dans le fichier fich
  // l'image de taille lrow lignes et ncol colonnes
  // dont les pixels sont rangés ligne par ligne dans le tableau ims
  // Retourne 0 si succès et un nombre non nul en cas d'erreur.
  static int savebmpgray(const char *fich, unsigned char*  ims, int nrow, int ncol);

  // Stocke dans les variables entières pointées par pnl et pnc
  // le nombre de lignes et le nombre de colonnes
  // de l'image contenue dans le fichier nommé fic
  //
  // Le fichier nommé fic doit être au format BMP en niveau de gris.
  //
  // Retourne 0 si succès et un nombre non nul en cas d'erreur.
  static int readsizebmpgray(const char *fic, int *pnl, int *pnc);

  // Lit les pixels de l'image contenue dans le fichier nommé fic
  // et les stocke dans le tableau pixelTab contenant nb elements.
  //
  // Le fichier nommé fic doit être au format BMP en niveau de gris.
  //
  // Le tableau pixelTab doit etre préalablement alloué.
  // Si le nombre d'element nb du tableau n'est pas assez grand pour contenir toute l'image,
  // un code erreur est retourné.
  //
  // On rappelle que le nb de lignes et de colonnes de l'image dans le fichier
  // peut être obtenu avec la fonction readsizebmpgray(...)
  //
  // Retourne 0 si succès et un nombre non nul en cas d'erreur.
  static int readpixelsbmpgray(const char *fic, unsigned char * pixelTab, int nb);
};

#endif
