#include "../include/lecturePPM.h"
#include <stdlib.h>
#include <stdio.h>

infoPPM* informations_PPM(FILE* f) {
    char magic[3];
    int largeur, hauteur, couleurMax;

    // Lecture du Magic Number
    if (fscanf(f, "%2s", magic) != 1 || strcmp(magic, "P6") != 0) {
        fprintf(stderr, "Erreur : Ce n'est pas un fichier P6 binaire\n");
        return NULL;
    }

    // Sauter les commentaires et lire Largeur, Hauteur, CouleurMax
    // On utilise une boucle pour ignorer tout ce qui commence par '#'
    int c = fgetc(f);
    while (c == '#' || c == ' ' || c == '\n' || c == '\r' || c == '\t') {
        if (c == '#') {
            while (fgetc(f) != '\n'); // Sauter la ligne de commentaire
        }
        c = fgetc(f);
    }
    ungetc(c, f); // On remet le premier chiffre dans le flux

    if (fscanf(f, "%d %d %d", &largeur, &hauteur, &couleurMax) != 3) {
        fprintf(stderr, "Erreur lors de la lecture des dimensions\n");
        return NULL;
    }

    // Sauter UN SEUL caractère blanc (souvent '\n') juste avant les données binaires
    fgetc(f);

    // Allocation et lecture
    infoPPM* p = malloc(sizeof(infoPPM));
    p->largeur = largeur;
    p->hauteur = hauteur;
    p->couleurMax = couleurMax;

    // Allocation en tableau 1D (plus propre avec fread)
    p->pixels = malloc(largeur * hauteur * sizeof(pixel));
    
    if (fread(p->pixels, sizeof(pixel), largeur * hauteur, f) != (size_t)(largeur * hauteur)) {
        fprintf(stderr, "Erreur : Données de pixels incomplètes\n");
        free(p->pixels);
        free(p);
        return NULL;
    }

    return p;
}