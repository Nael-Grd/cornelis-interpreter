#ifndef COULEUR_H
#define COULEUR_H
#include "lecturePPM.h"

typedef enum {
    rouge_fonce,
    rouge_normal,
    rouge_clair,
    jaune_fonce,
    jaune_normal,
    jaune_clair,
    vert_fonce,
    vert_normal,
    vert_clair,
    bleu_fonce,
    bleu_normal,
    bleu_clair,
    cyan_fonce,
    cyan_normal,
    cyan_clair,
    magenta_fonce,
    magenta_normal,
    magenta_clair,
    autre
}couleur;

/*@requires nothing
@assigns nothing
@ensures return the luminance of a pixel */
int luminance(pixel p);

/*@requires nothing
@assigns nothing
@ensures return 1 if the pixel is a passing color, 0 otherwise */
int estPassante(pixel p);

/*@requires nothing
@assigns nothing
@ensures return the color of a coding color pixel */
couleur nom_couleur(pixel p);

/*@requires nothing
@assigns nothing
@ensures return the difference in notch between 2 colors and -1 if colors are not coding */
int dif_couleur(couleur c1,couleur c2);

/*@requires nothing
@assigns nothing
@ensures return the difference of brightness between 2 colors and -1 if colors are not coding */
int dif_luminosite(couleur c1, couleur c2);

#endif




