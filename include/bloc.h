#ifndef BLOC_H
#define BLOC_H
 
#include "couleur.h"   

typedef enum {   
    EST,
    SUD,
    OUEST,
    NORD
} direction;

typedef enum {    
    BABORD,
    TRIBORD
} bord;

typedef struct { int x, y; } Point;

/*@requires valid adress for info
@assigns traite
@ensures return the table with 1 for the block and 0 elsewhere */
int** traitement(infoPPM* info, couleur init, int x, int y, int** traite);

/*@requires bloc a table with 1 for the block and 0 elsewhere, the height and the width of the picture
@assigns nothing
@ensures return lenght of a block */
int taille_bloc(int** bloc, int largeur, int hauteur);

/*@requires valid adress for info
@assigns nothing
@ensures return the number of blocks in the picture */
int nombre_blocs(infoPPM* info, int** traite);

/*@requires nothing
@assigns nothing
@ensures change the border */
bord changer_bord(bord b);

/*@requires nothing
@assigns nothing
@ensures change the direction */
direction changer_direction(direction d);

/*@requires height and width of the image
@assigns nothing
@ensures return the coordinates of the pixel of the following block */
Point pixel_suivant(int** bloc, direction d, bord b, int hauteur, int largeur);

#endif





