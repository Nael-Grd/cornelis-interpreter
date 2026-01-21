#include "lecturePPM.h"
#include <string.h>
#include <stdlib.h>

infoPPM* informations_PPM(FILE* f) {
    char buffer[128];
    fgets(buffer, 128, f);      //lecture de la 1ere ligne du fichier (P6)
    if (strcmp(buffer, "P6\n"))       //on verifie si le fichier est en format binaire PPM
        perror("fichier PPM non binaire\n");
    
    int largeur, hauteur, couleurMax;
    fgets(buffer, 128, f);         //lecture de la 2e ligne (commentaires) on ne fait rien avec
    fgets(buffer, 128, f);
    sscanf(buffer, "%d %d", &largeur, &hauteur);  //extraction de la largeur et de la hauteur
    fgets(buffer, 128, f);           //lecture de la 3e ligne (couleur max)
    sscanf(buffer, "%d", &couleurMax);  //extraction de la couleur max

    infoPPM* p=malloc(sizeof(infoPPM));  //on alloue la memoire pour notre structure
    p->largeur=largeur;             //on assigne les informations
    p->hauteur=hauteur;  
    p->couleurMax=couleurMax;
    p->pixels = malloc(largeur*hauteur*sizeof(pixel));    //on alloue notre tableau de pixels aux bonnes dimensions
    fread(p->pixels, sizeof(pixel), largeur*hauteur, f);  //lecture des informations des pixels dans notre tableau
    return p;  
}





