#include "../include/bloc.h"
#include <string.h>
#include <stdlib.h>

// Fonction auxilliaire pour traitement
void explorer_bloc(infoPPM* info, couleur init, int x, int y, int** traite) {

    if (x < 0 || x >= info->largeur || y < 0 || y >= info->hauteur) {   // si on est toujours dans l'image
        return;
    }

    if (traite[y][x] == 1) return; 

    if (nom_couleur(info->pixels[y * info->largeur + x]) != init) return; // Pas la bonne couleur

    traite[y][x] = 1; // traité

    explorer_bloc(info, init, (x + 1) % info->largeur, y, traite);
    explorer_bloc(info, init, (x - 1 + info->largeur) % info->largeur, y, traite);
    explorer_bloc(info, init, x, (y + 1) % info->hauteur, traite);
    explorer_bloc(info, init, x, (y - 1 + info->hauteur) % info->hauteur, traite);
}

int** traitement(infoPPM* info, couleur init, int x, int y, int** traite) {
    for(int i = 0; i < info->hauteur; i++) {
        for(int j = 0; j < info->largeur; j++) traite[i][j] = 0;
    }
    explorer_bloc(info, init, x, y, traite);
    return traite;
}

bord changer_bord(bord b) {
    if (b==BABORD)
        return TRIBORD;
    else
        return BABORD;
}

direction changer_direction(direction d) {
    switch(d) {
        case EST:
            return SUD;
            break;
        case SUD:
            return OUEST;
            break;
        case OUEST: 
            return NORD;
            break;
        case NORD: 
            return EST;
            break;
        default:               
            return d;
    }
}

int taille_bloc(int** bloc, int largeur, int hauteur) {
    int i, j;
    int cpt=0;
    for (i=0; i<hauteur; i++) {          // On parcourt le tableau et on compte le nombre de 1 
        for (j=0; j<largeur; j++) {
            if (bloc[i][j] == 1)
                cpt+=1;
        }
    }
    return cpt;
}

int nombre_blocs(infoPPM* info, int** traite) {
    int hauteur = info->hauteur;
    int largeur = info->largeur;
    int blocs = 0;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            traite[i][j] = 0;
        }
    }

    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            if (traite[y][x] == 0) { 
                blocs++;         // nouveau bloc
                couleur c = nom_couleur(info->pixels[y * largeur + x]);
                explorer_bloc(info, c, x, y, traite);   // exploration récurssive
            }
        }
    }
    return blocs;
}



Point pixel_suivant(int** bloc, direction d, bord b, int hauteur, int largeur) {
    Point res = {0, 0};
    int frontiere = -1;

    // Recherche frontière
    switch (d) {
        case EST:
            for (int x = largeur - 1; x >= 0; x--) {
                for (int y = 0; y < hauteur; y++) {
                    if (bloc[y][x] == 1) { frontiere = x; break; }
                }
                if (frontiere != -1) break;
            }
            res.x = frontiere;
            break;

        case OUEST:
            for (int x = 0; x < largeur; x++) {
                for (int y = 0; y < hauteur; y++) {
                    if (bloc[y][x] == 1) { frontiere = x; break; }
                }
                if (frontiere != -1) break;
            }
            res.x = frontiere;
            break;

        case NORD:
            for (int y = 0; y < hauteur; y++) {
                for (int x = 0; x < largeur; x++) {
                    if (bloc[y][x] == 1) { frontiere = y; break; }
                }
                if (frontiere != -1) break;
            }
            res.y = frontiere;
            break;

        case SUD:
            for (int y = hauteur - 1; y >= 0; y--) {
                for (int x = 0; x < largeur; x++) {
                    if (bloc[y][x] == 1) { frontiere = y; break; }
                }
                if (frontiere != -1) break;
            }
            res.y = frontiere;
            break;
    }

    if (frontiere == -1) {   // si aucun pixel trouvé 
        return res; 
    }

    // Recherche pixel sur frontière
    switch (d) {
        case EST:
            if (b == BABORD) { // Haut (Y min)
                for (int y = 0; y < hauteur; y++) {
                    if (bloc[y][frontiere] == 1) { res.y = y; break; }
                }
            } else { // Bas (Y max)
                for (int y = hauteur - 1; y >= 0; y--) {
                    if (bloc[y][frontiere] == 1) { res.y = y; break; }
                }
            }
            break;

        case OUEST:
            if (b == BABORD) { // Bas (Y max)
                for (int y = hauteur - 1; y >= 0; y--) {
                    if (bloc[y][frontiere] == 1) { res.y = y; break; }
                }
            } else { // Haut (Y min)
                for (int y = 0; y < hauteur; y++) {
                    if (bloc[y][frontiere] == 1) { res.y = y; break; }
                }
            }
            break;

        case NORD:
            if (b == BABORD) { // Gauche (X min)
                for (int x = 0; x < largeur; x++) {
                    if (bloc[frontiere][x] == 1) { res.x = x; break; }
                }
            } else { // Droite (X max)
                for (int x = largeur - 1; x >= 0; x--) {
                    if (bloc[frontiere][x] == 1) { res.x = x; break; }
                }
            }
            break;

        case SUD:
            if (b == BABORD) { // Droite (X max)
                for (int x = largeur - 1; x >= 0; x--) {
                    if (bloc[frontiere][x] == 1) { res.x = x; break; }
                }
            } else { // Gauche (X min)
                for (int x = 0; x < largeur; x++) {
                    if (bloc[frontiere][x] == 1) { res.x = x; break; }
                }
            }
            break;
    }

    return res;
}