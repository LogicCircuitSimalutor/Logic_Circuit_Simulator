#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BmpIO.h"

typedef unsigned char* IMAGE8;
typedef unsigned int* IMAGE24;

static unsigned char ** alloue_image(int nl, int nc) {
    int i;
    unsigned char** p;
    if ( (p=(unsigned char**)calloc(nl,sizeof(*p)))==NULL) return NULL;
    if ( (*p=(unsigned char*)calloc(nl*nc,sizeof(**p)))==NULL) return NULL;
    for (i=1; i<nl; i++) p[i]=p[i-1]+nc;
    return p;
}


// ajout NC
void freebmpimage(unsigned char ** img) {
    int i;
    for(i = 0 ; i < 1000 ; i ++) {
        (*img)[i] = 0;
    }

    free(*img);
    free(img);
}


#define ecritc(c,fp)        putc(c,fp)

static void ecriti(int i, FILE* fp)
{   int b0,b1,b2,b3;
    b0 = (((unsigned int) i)) & 0xFF;
    b1 = (((unsigned int) i)>>8) & 0xFF;
    b2 = (((unsigned int) i)>>16) & 0xFF;
    b3 = (((unsigned int) i)>>24) & 0xFF;
    putc(b0,fp);
    putc(b1,fp);
    putc(b2,fp);
    putc(b3,fp);
}

static void ecrits(short i, FILE* fp)
{   int b0,b1;
    b0 = (((unsigned int) i)) & 0xFF;
    b1 = (((unsigned int) i)>>8) & 0xFF;
    putc(b0,fp);
    putc(b1,fp);
}
/* Construit l'entete general. */
static void EnteteBmp(FILE * fp,int nrow,int ncol, int nbbits) {
    int		bl, nc;
    int		ll;

    ecritc('B',fp);
    ecritc('M',fp);		// Magic number
    ll = (((ncol * nbbits) + 31) / 32)*4; 	// Taille d'une ligne.
    if (nbbits == 24)
        nc=0;
    else
        nc = 256;
    bl = 14+40+(nc*4);
    ecriti(bl + (ll*nrow),fp);
    ecrits(0,fp);				// Reserved.
    ecrits(0,fp);
    ecriti(bl,fp);				// bfoffbits.

    ecriti(40,fp);
    ecriti(ncol,fp);
    ecriti(nrow,fp);
    ecrits(1,fp);
    ecrits(nbbits,fp);
    ecriti(0,fp);
    ecriti(ll*nrow,fp);
    ecriti(75*39,fp);
    ecriti(75*39,fp);
    ecriti(nc,fp);
    ecriti(nc,fp);
}

/* Transforme un octet image en sa valeur hexadecimale affichable (LUT). */
static void CouleursBmp(FILE* df)
{
    for (int i=0; i<256; i++) {
        ecritc(i,df);
        ecritc(i,df);
        ecritc(i,df);
        ecritc(0,df);
    }
}

/* Sauvegarde des données 8 bits.*/
static void Donnees8Bmp(FILE* df,IMAGE8 ims, int nrow, int ncol)
{   int		bf,i,j;

    bf = ((ncol+3)/4) * 4;
    for(i=nrow-1; i>=0; i--) {
        for(j=0; j<ncol; j++) ecritc(ims[i*ncol+j],df);
        for(; j<bf; j++) ecritc(0,df);
    }
}

/*  Sauvegarde des données 24 bits. */
static void Donnees24Bmp(FILE* df,IMAGE24 ims, int nrow, int ncol)
{
    int bf,i,j;

    bf = (4-((ncol*3)%4)) & 0x03; 	// panding 32 bits.
    for(i=nrow-1; i>=0; i--) {
        for(j=0; j<ncol; j++) {
            ecritc((unsigned char )(ims[i*ncol+j]&0x000000ff),df);
            ecritc((unsigned char )((ims[i*ncol+j]&0x0000ff00)>>8),df);
            ecritc((unsigned char)((ims[i*ncol+j]&0x00ff0000)>>16),df);
        }
        for (j=0; j<bf; j++) ecritc(0,df);
    }
}


/* * Conclue le fichier Bmp.  */
static void EpilogueBmp(FILE* df)
{ }

static int ecrit8bmp(const char *fich, IMAGE8 ims, int nrow, int ncol)
{
    //printf("ecrit8bmp %s\n", fich); getchar();
    FILE*	dfd;
    if  (!(dfd = fopen(fich,"wb"))) {
        fprintf(stderr,"Impossible de creer le fichier BMP %s\n",fich);
        return(-1);
    }
    EnteteBmp(dfd,nrow,ncol,8);
    CouleursBmp(dfd);
    Donnees8Bmp(dfd,ims,nrow,ncol);
    EpilogueBmp(dfd);
    fclose(dfd);
    return(0);
}

static int ecrit24bmp(char *fich, IMAGE24 ims, int nrow, int ncol)
{   FILE* dfd;
    if  (!(dfd = fopen(fich,"wb"))) {
        fprintf(stderr,"Impossible de creer le fichier BMP %s\n",fich);
        return(-1);
    }
    EnteteBmp(dfd,nrow,ncol,24);
    Donnees24Bmp(dfd,ims,nrow,ncol);
    EpilogueBmp(dfd);
    fclose(dfd);
    return(0);
}

//#define DEBUG

/* BMP format constants. */
#define BI_RGB		0
#define BI_RLE8		1
#define BI_RLE4		2

#define WIN_OS2_OLD	12
#define WIN_NEW		40
#define OS2_NEW		64
#define SUCCESS 1
#define FAILURE -1



/**
 * Reads a character.
 */
#define	readc(fp) getc(fp)

/**
 * Reads a short.
 */
static unsigned int reads( FILE *fp ) {
    int b0, b1;

    b0 = getc(fp);
    b1 = getc(fp);
    return ((unsigned int) b0) + (((unsigned int) b1) << 8);
}

/**
 * Reads an integer.
 */
static unsigned int readi( FILE *fp ) {
    int b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);
    return ((unsigned int) b0) +(((unsigned int) b1) << 8) + (((unsigned int) b2) << 16) + (((unsigned int) b3) << 24);
}

/**
 * Reads image data for black and white images.
 * @param fp the input file.
 * @param imd the output Pandore image.
 */
static int  ReadBlackWhiteData(FILE *fp, unsigned char** imd, int nl, int nc ) {
    int	i,j,k;
    int	ob;
    int	b0;
    unsigned char *p;

#ifdef DEBUG
    printf("-> Black and White image\n");
#endif

    b0 = 0;
    ob = ((nc + 31)/32) * 32;  /* offset for 32 bits length lines */
    for (i=nl-1; i>=0; i--) {
        p = &imd[i][0];
        for (j=k=0; j<ob; j++,k++) {
            if ((k&7) == 0) { /* next byte */
                b0 = readc(fp);
                k = 0;
            }
            if (j<nc) {
                *p++ = (b0 & 0x80) ? 255 : 0;
                b0 <<= 1;
            }
        }
    }
    return SUCCESS;
}

/**
 * Reads image data for grayscale images.
 * @param fp the input file.
 * @param imd the output Pandore image.
 */
static int ReadGrayscaleData(FILE *fp, unsigned char**imd, int nbit, unsigned char lut[][3], int compression,int nl,int nc ) {
    int	i,j,k, x, y;
    int	ob;
    int	b0, b1;
    unsigned char *p;

#ifdef DEBUG
    printf("-> Grayscale image\n");
#endif

    b0 = 0;
    if (nbit == 4) {	/* 4 bits */
        b0 = b1 = 0;
        if (compression == BI_RGB) {   /* no compression */
            ob = ((nc + 7)/8) * 8; /* complement to 32 bits */

            for (i=nl-1; i>=0; i--) {
                p = &imd[i][0];
                for (j=k=0; j<ob; j++,k++) {
                    if ((k & 1) == 0) { /* next byte */
                        b0 = readc(fp);
                        k = 0;
                    }
                    if (j<nc) {
                        *p++ = (b0 & 0xf0) >> 4;
                        b0 <<= 4;
                    }
                }
            }
        } else if (compression == BI_RLE4) { /* RLE compression format */
            x = y = 0;
            p = &imd[nl-y-1][x];
            while (y<nl) {
                b0 = readc(fp);
                if (b0) {
                    b1 = readc(fp);
                    for (i=0; i<b0; i++,x++,p++)
                        *p = (i&1) ? (b1 & 0x0f) : ((b1>>4) & 0x0f);
                } else {	/* b0==0  :  escape codes */
                    b0 = readc(fp);
                    if (b0 == 0x00) {	/* end of line */
                        x=0;
                        y++;
                        p = &imd[nl-y-1][x];
                    } else if (b0 == 0x01) {
                        break;		/* end of data */
                    } else if (b0 == 0x02) {	/* delta */
                        b0 = readc(fp);
                        x += b0;
                        b0 = readc(fp);
                        y += b0;
                        p = &imd[nl-y-1][x];
                    } else {		/* absolute mode */
                        for (i=0; i<b0; i++, x++, p++) {
                            if ((i&1) == 0)
                                b1 = readc(fp);
                            *p = (i&1) ? (b1 & 0x0f) : ((b1>>4) & 0x0f);
                        }
                        if (((b0&3)==1) || ((b0&3)==2))
                            readc(fp);  /* Skip end of line*/
                    }
                }
            }
        } else {
            fprintf(stderr, "Error: Unknow compression format\n");
            return FAILURE;
        }
    } else if (nbit == 8) {	/* 8 bits */
        if (compression == BI_RGB) {   /* no compression */
            ob = ((nc + 3)/4) * 4; /* complement to 32 bits */
            for (i=nl-1; i>=0; i--) {
                for (j=0; j<ob; j++) {
                    b0 = readc(fp);
                    if (j<nc)
                        imd[i][j] = b0;
                }
            }
        } else if (compression == BI_RLE8) {  /* RLE compression format */
            x = y = 0;
            p = &imd[nl-y-1][x];
            while (y<nl) {
                b0 = readc(fp);
                if (b0) {	/* encoded mode */
                    b1 = readc(fp);
                    for (i=0; i<b0; i++,x++,p++)
                        *p = b1;
                } else {   /* b0==0  :  escape codes */
                    b0 = readc(fp);
                    if (b0 == 0x00) {	/* end of line */
                        x=0;
                        y++;
                        p = &imd[nl-y-1][x];
                    } else if (b0 == 0x01)
                        break;	/* end of data */
                    else if (b0 == 0x02) {	/* delta */
                        b0 = readc(fp);
                        x += b0;
                        b0 = readc(fp);
                        y += b0;
                        p = &imd[nl-y-1][x];
                    } else {
                        for (i=0; i<b0; i++, x++, p++) {
                            b1 = readc(fp);
                            *p = b1;
                        }
                        if (b0 & 1)
                            readc(fp);
                    }
                }
            }
        } else {
            fprintf(stderr,"Error: Unknown format\n");
            return FAILURE;
        }
    }

    // applies the lut transform.
    for (i = 0; i<nl; i++)
        for (j = 0; j<nc; j++) {
            imd[i][j] = lut[imd[i][j]][0];
        }

    return SUCCESS;
}

/**
 * Reads image data for grayscale images.
 * @param fp the input file.
 * @param imd the output Pandore image.
 */
static int ReadColorData(FILE *fp, unsigned char** X,unsigned char** Y, unsigned char** Z, int nbit, unsigned char lut[][3], int compression,int nl, int nc ) {
    int	i,j,k,x,y;
    int	ob;
    int	b0, b1;
    unsigned char *p;

    b0 = 0;
    if (nbit == 4) {	/* 4 bits */
#ifdef DEBUG
        printf("-> Color image 4 bits\n");
#endif
        b0 = b1 = 0;

        if (compression == BI_RGB) {   /* no compression */
            ob = ((nc + 7)/8) * 8; /* complement to 32 bits */

            for (i=nl-1; i>=0; i--) {
                p = &X[i][0];
                for (j=k=0; j<ob; j++,k++) {
                    if ((k & 1) == 0) { /* next byte */
                        b0 = readc(fp);
                        k = 0;
                    }
                    if (j<nl) {
                        *p++ = (b0 & 0xf0) >> 4;
                        b0 <<= 4;
                    }
                }
            }
        } else if (compression == BI_RLE4) { /* RLE4 compression format */
#ifdef DEBUG
            printf("    with RLE encoding\n");
#endif
            x = y = 0;
            p = &X[nl-y-1][x];
            while (y<nl) {
                b0 = readc(fp);
                if (b0) {
                    b1 = readc(fp);
                    for (i=0; i<b0; i++,x++,p++)
                        *p = (i&1) ? (b1 & 0x0f) : ((b1>>4) & 0x0f);
                } else {	/* b0==0  :  escape codes */
                    b0 = readc(fp);
                    if (b0 == 0x00) {	/* end of line */
                        x=0;
                        y++;
                        p = &X[nl-y-1][x];
                    } else if (b0 == 0x01) {
                        break;		/* end of data */
                    } else if (b0 == 0x02) {	/* delta */
                        b0 = readc(fp);
                        x += b0;
                        b0 = readc(fp);
                        y += b0;
                        p = &X[nl-y-1][x];
                    } else {		/* absolute mode */
                        for (i=0; i<b0; i++, x++, p++) {
                            if ((i&1) == 0)
                                b1 = readc(fp);
                            *p = (i&1) ? (b1 & 0x0f) : ((b1>>4) & 0x0f);
                        }
                        if (((b0&3)==1) || ((b0&3)==2))
                            readc(fp);  /* skip end of line */
                    }
                }
            }
        } else {
            fprintf(stderr, "Error: Unknow compression format\n");
            return FAILURE;
        }
        // Applies the lut transform.
        for ( i = 0; i<nl; i++)
            for ( j = 0; j<nc; j++) {
                unsigned char c=X[i][j];
                Z[i][j] = lut[c][0];
                Y[i][j] = lut[c][1];
                X[i][j] = lut[c][2];
            }

    } else if (nbit == 8) {	/* 8 Bits */
#ifdef DEBUG
        printf("-> Color image 8 bits\n");
#endif
        if (compression == BI_RGB) {   /* no compression */
            ob = ((nc + 3)/4) * 4; /* complement to 32 bits */
            for (i=nl-1; i>=0; i--) {
                for (j=0; j<ob; j++) {
                    b0 = readc(fp);
                    if (j<nc) {
                        X[i][j] = lut[b0][2];
                        Y[i][j] = lut[b0][1];
                        Z[i][j] = lut[b0][0];
                    }
                }
            }
        } else if (compression == BI_RLE8) {  /* RLE compression format */
#ifdef DEBUG
            printf("    with RLE encoding\n");
#endif
            x = y = 0;
            p = &X[nl-y-1][x];
            while (y<nl) {
                b0 = readc(fp);
                if (b0) {	/* encoded mode */
                    b1 = readc(fp);
                    for (i=0; i<b0; i++,x++,p++)
                        *p = b1;
                } else {    /* b0==0  :  escape codes */
                    b0 = readc(fp);
                    if (b0 == 0x00) {	/* end of line */
                        x=0;
                        y++;
                        p = &X[nl-y-1][x];
                    } else if (b0 == 0x01)
                        break;	/* end of data */
                    else if (b0 == 0x02) {	/* delta */
                        b0 = readc(fp);
                        x += b0;
                        b0 = readc(fp);
                        y += b0;
                        p = &X[nl-y-1][x];
                    } else {
                        for (i=0; i<b0; i++, x++, p++) {
                            b1 = readc(fp);
                            *p = b1;
                        }
                        if (b0 & 1)
                            readc(fp);
                    }
                }
            }
            // Applies the lut transform.
            for ( i = 0; i<nl; i++)
                for ( j = 0; j<nc; j++) {
                    unsigned char c=X[i][j];
                    Z[i][j] = lut[c][0];
                    Y[i][j] = lut[c][1];
                    X[i][j] = lut[c][2];
                }
        } else {
            fprintf(stderr,"Error: Unknown format\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}

/*
 * Reads data for color images.
 * @param fp the input file.
 * @param imd the output Pandore image.
 */
static int ReadTrueColorsData( FILE *fp, unsigned char** X, unsigned char** Y, unsigned char** Z, int nl, int nc) {
    int i,j,bf;

#ifdef DEBUG
    printf("-> True colors image\n");
#endif

    bf = (4 - ((nc*3) % 4)) & 0x03;  /* complement to 32 bits. */

    for (i=nl-1; i>=0; i--) {
        // Lit les couleurs.
        for (j=0; j<nc; j++) {
            Z[i][j] = (unsigned char)readc(fp);   /* red */
            Y[i][j] = (unsigned char)readc(fp);   /* green */
            X[i][j] = (unsigned char)readc(fp);   /* blue */
        }
        // Skip end of lines (complement to 32 bits).
        for (j=0; j<bf; j++)
            readc(fp);
    }
    return SUCCESS;
}


int readbmpgray( const char* fic, unsigned char***img, int *nl, int *nc) {
    int offset, filesize;
    int result=SUCCESS;
    unsigned long	nlig,ncol, nbit;
    unsigned char lut[256][3];
    int b, m;
    unsigned int	i;
    unsigned int	bfSize, bfOffBits, biSize, biWidth, biHeight, biPlanes;
    unsigned int	biBitCount, biCompression, biSizeImage, biXPelsPerMeter;
    unsigned int	biYPelsPerMeter, biClrUsed, biClrImportant;

    FILE*fp = fopen(fic,"r");
    if (fp==NULL) return FAILURE;

    fseek(fp,0L,SEEK_END);
    filesize = ftell(fp);
    fseek(fp,0L,SEEK_SET);

    // 1. FILE HEADER.
    b = readc(fp);
    m = readc(fp);
    if (!
            (b=='B' && m=='M') ||	// Windows Bitmap
            (b=='B' && m=='A') ||	// OS/2 Bitmap
            (b=='C' && m=='I') ||	// OS/2 color icon
            (b=='C' && m=='P') ||	// OS/2 icon
            (b=='I' && m=='C') ||	// OS/2 Pointer
            (b=='P' && m=='T') ) {
        fprintf(stderr,"Error: Bad BMP file\n");
        return FAILURE;
    }

    bfSize = readi(fp);		// file size.
    readi(fp);			// unused

    bfOffBits = readi(fp);	// data offset.

    // 2. INFORMATION HEADER
    biSize = readi(fp);
    if (biSize == WIN_NEW || biSize == OS2_NEW) { // case header size = WIN_NEW bytes.
        biWidth         = readi(fp);
        biHeight        = readi(fp);
        biPlanes        = reads(fp);
        biBitCount      = reads(fp);
        biCompression   = readi(fp);
        biSizeImage     = readi(fp);
        biXPelsPerMeter = readi(fp);
        biYPelsPerMeter = readi(fp);
        biClrUsed       = readi(fp);
        biClrImportant  = readi(fp);
    } else {    // Old format.
        biWidth         = reads(fp);
        biHeight        = reads(fp);
        biPlanes        = reads(fp);
        biBitCount      = reads(fp);
        biSizeImage = (((biPlanes * biBitCount*biWidth)+31)/32)*4*biHeight;
        biCompression   = BI_RGB;
        biXPelsPerMeter = biYPelsPerMeter = 0;
        biClrUsed       = biClrImportant  = 0;
    }

    // Check properties consistency.
    if (((biBitCount==1 || biBitCount==24) && biCompression != BI_RGB) ||
            (biBitCount==4 && biCompression==BI_RLE8) ||
            (biBitCount==8 && biCompression==BI_RLE4) ||
            (biBitCount!=1 && biBitCount!=4 && biBitCount!=8 && biBitCount!=24) ||
            biPlanes!=1 || biCompression>BI_RLE4) {
        fprintf(stderr,"Error: Bad BMP format\n");
        return FAILURE;
    }

#ifdef  DEBUG
    printf("Width=%d\n",biWidth);
    printf("height=%d\n",biHeight);
    printf("planes=%d\n",biPlanes);
    printf("bit count=%d\n",biBitCount);
    printf("compression =%d\n",biCompression);
    printf("image size=%d\n",biSizeImage);
    printf("x pixel per meter=%d\n",biXPelsPerMeter);
    printf("y pixel per meter=%d\n",biYPelsPerMeter);
    printf("color number=%d\n",biClrUsed);
    printf("important colors =%d\n",biClrImportant);
#endif

    offset = 0;

    // skip to colors.
    if (biSize != WIN_OS2_OLD) {
        for (i=0; i<(biSize-40); i++)
            readc(fp);
        // BMP error : bad file size -> skip to the end of file.
        offset = bfOffBits - (biSize + 14);
    }

    // load colors.
    char colorImage = 0; // flag 1 if it is a color image, 0 if is a grayscale image.
    if (biBitCount!=24) {
        ncol = (biClrUsed) ? biClrUsed : 1 << biBitCount;
        for (i=0; i<ncol; i++) {
            lut[i][0] = readc(fp);
            lut[i][1] = readc(fp);
            lut[i][2] = readc(fp);
            // determines if it is grayscale image
            // or a color image.
            if (lut[i][0] != lut[i][1] || lut[i][0] != lut[i][2] || lut[i][1] != lut[i][2])
                colorImage=1;
            if (biSize != WIN_OS2_OLD) {
                readc(fp);
                offset -= 4;
            }
        }
    } else {	// skip colors.
        offset = bfSize - filesize - offset;
    }
    // skip to data.
    if (biSize != WIN_OS2_OLD) {
        while (offset > 0) {
            (void) readc(fp);
            offset--;
        }
    }

    *nc=ncol = biWidth;
    *nl=nlig = biHeight;
    nbit = biBitCount;
    if (colorImage) {
        return FAILURE;
    }

    if (nbit == 1) {
        *img = alloue_image(nlig,ncol);
        result=ReadBlackWhiteData(fp,*img,nlig,ncol);
    } else if (nbit == 4 || nbit==8) {
        *img = alloue_image(nlig,ncol);
        result=ReadGrayscaleData(fp,*img,nbit, lut,biCompression,nlig,ncol);
    } else
        return FAILURE;

    return result;
}


/*
 * Converts the input BMP file
 * into the output Pandore image.
 * @param fp the input file.
 * @param objout the output Pandore image.
 * @return SUCCESS or FAILURE.
 */
static int  readbmpcolor( char* fic, unsigned char***X, unsigned char***Y, unsigned char***Z, int *nl, int *nc ) {
    int offset, filesize;
    int result=SUCCESS;
    unsigned long	nlig,ncol, nbit;
    unsigned char lut[256][3];
    int b, m;
    unsigned int	i;
    unsigned int	bfSize, bfOffBits, biSize, biWidth, biHeight, biPlanes;
    unsigned int	biBitCount, biCompression, biSizeImage, biXPelsPerMeter;
    unsigned int	biYPelsPerMeter, biClrUsed, biClrImportant;

    FILE *fp=fopen(fic,"r");
    if (fp==NULL) return FAILURE;

    fseek(fp,0L,SEEK_END);
    filesize = ftell(fp);
    fseek(fp,0L,SEEK_SET);

    // 1. FILE HEADER.
    b = readc(fp);
    m = readc(fp);
    if (!
            (b=='B' && m=='M') ||	// Windows Bitmap
            (b=='B' && m=='A') ||	// OS/2 Bitmap
            (b=='C' && m=='I') ||	// OS/2 color icon
            (b=='C' && m=='P') ||	// OS/2 icon
            (b=='I' && m=='C') ||	// OS/2 Pointer
            (b=='P' && m=='T') ) {
        fprintf(stderr,"Error: Bad BMP file\n");
        return FAILURE;
    }

    bfSize = readi(fp);		// file size.
    readi(fp);			// unused

    bfOffBits = readi(fp);	// data offset.

    // 2. INFORMATION HEADER
    biSize = readi(fp);
    if (biSize == WIN_NEW || biSize == OS2_NEW) { // case header size = WIN_NEW bytes.
        biWidth         = readi(fp);
        biHeight        = readi(fp);
        biPlanes        = reads(fp);
        biBitCount      = reads(fp);
        biCompression   = readi(fp);
        biSizeImage     = readi(fp);
        biXPelsPerMeter = readi(fp);
        biYPelsPerMeter = readi(fp);
        biClrUsed       = readi(fp);
        biClrImportant  = readi(fp);
    } else {    // Old format.
        biWidth         = reads(fp);
        biHeight        = reads(fp);
        biPlanes        = reads(fp);
        biBitCount      = reads(fp);
        biSizeImage = (((biPlanes * biBitCount*biWidth)+31)/32)*4*biHeight;
        biCompression   = BI_RGB;
        biXPelsPerMeter = biYPelsPerMeter = 0;
        biClrUsed       = biClrImportant  = 0;
    }

    // Check properties consistency.
    if (((biBitCount==1 || biBitCount==24) && biCompression != BI_RGB) ||
            (biBitCount==4 && biCompression==BI_RLE8) ||
            (biBitCount==8 && biCompression==BI_RLE4) ||
            (biBitCount!=1 && biBitCount!=4 && biBitCount!=8 && biBitCount!=24) ||
            biPlanes!=1 || biCompression>BI_RLE4) {
        fprintf(stderr,"Error: Bad BMP format\n");
        return FAILURE;
    }

#ifdef  DEBUG
    printf("Width=%d\n",biWidth);
    printf("height=%d\n",biHeight);
    printf("planes=%d\n",biPlanes);
    printf("bit count=%d\n",biBitCount);
    printf("compression =%d\n",biCompression);
    printf("image size=%d\n",biSizeImage);
    printf("x pixel per meter=%d\n",biXPelsPerMeter);
    printf("y pixel per meter=%d\n",biYPelsPerMeter);
    printf("color number=%d\n",biClrUsed);
    printf("important colors =%d\n",biClrImportant);
#endif

    offset = 0;

    // skip to colors.
    if (biSize != WIN_OS2_OLD) {
        for (i=0; i<(biSize-40); i++)
            readc(fp);
        // BMP error : bad file size -> skip to the end of file.
        offset = bfOffBits - (biSize + 14);
    }

    // load colors.
    char colorImage = 0; // flag 1 if it is a color image, 0 if is a grayscale image.
    if (biBitCount!=24) {
        ncol = (biClrUsed) ? biClrUsed : 1 << biBitCount;
        for (i=0; i<ncol; i++) {
            lut[i][0] = readc(fp);
            lut[i][1] = readc(fp);
            lut[i][2] = readc(fp);
            // determines if it is grayscale image
            // or a color image.
            if (lut[i][0] != lut[i][1] || lut[i][0] != lut[i][2] || lut[i][1] != lut[i][2])
                colorImage=1;
            if (biSize != WIN_OS2_OLD) {
                readc(fp);
                offset -= 4;
            }
        }
    } else {	// skip colors.
        offset = bfSize - filesize - offset;
    }
    // skip to data.
    if (biSize != WIN_OS2_OLD) {
        while (offset > 0) {
            (void) readc(fp);
            offset--;
        }
    }

    *nc=ncol = biWidth;
    *nl=nlig = biHeight;
    nbit = biBitCount;

    if (!colorImage && nbit!=24) {
        return FAILURE;
    }
    *X=alloue_image(nlig,ncol);
    *Y=alloue_image(nlig,ncol);
    *Z=alloue_image(nlig,ncol);

    if (nbit == 4 || nbit==8) {
        result=ReadColorData(fp,*X,*Y,*Z,nbit, lut,biCompression,nlig,ncol);
    } else if (nbit == 24) {
        result=ReadTrueColorsData(fp,*X,*Y,*Z,nlig,ncol);
    } else
        return FAILURE;

    return result;
}

int BmpIO::savebmpgray(const char *fic, unsigned char*  ims, int nrow, int ncol) {
    return ecrit8bmp(fic,ims,nrow,ncol);
}



// note : fonctionnel, mais on écrirait pas cette fonction comme cela en fait !
int BmpIO::readsizebmpgray(const char *fic, int *pnl, int *pnc) {

    unsigned char** t;
    int nl, nc;
    if(readbmpgray(fic,&t,&nl,&nc) != 1) {
        //cout << "Pb lecture " << endl;
        return 1;
    }
    *pnl = nl;
    *pnc = nc;

    freebmpimage(t);
    return 0;
}




// note : fonctionnel, mais on écrirait pas cette fonction comme cela en fait !
int BmpIO::readpixelsbmpgray(const char *fic, unsigned char * pixelTab, int nb) {
    unsigned char** t;
    int nl, nc;
    if(readbmpgray(fic,&t,&nl,&nc) != 1) {
        //cout << "Pb lecture " << endl;
        return 1;
    }
    if(nb < nl*nc) {
        freebmpimage(t);
        return 2;
    }

    memcpy(pixelTab, *t, nl*nc*sizeof(*pixelTab));

    freebmpimage(t);
    return 0;
}
