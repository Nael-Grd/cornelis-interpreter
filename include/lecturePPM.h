#ifndef LECTUREPPM_H
#define LECTUREPPM_H

#include <stdio.h>

typedef struct pixel pixel;    
struct pixel {
    unsigned char rouge, vert, bleu;   //valeurs de 0 a 255
};
                       
typedef struct infoPPM infoPPM;  
struct infoPPM {
    int hauteur;
    int largeur;
    int couleurMax;
    pixel* pixels;    // tableau 1D de pixels
};


/*
@requires valid adress
@assigns an array
@ensures return an array with informations of the PPM file 
*/
infoPPM* informations_PPM(FILE* f);

#endif
