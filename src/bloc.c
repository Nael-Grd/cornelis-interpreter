#include "../include/bloc.h"
#include <string.h>
#include <stdlib.h>

// Fonction auxilliaire pour traitement
void explorer_bloc(infoPPM* info, couleur init, int x, int y, int** traite) {
    if (traite[x][y] == 1) return; 
    if (nom_couleur(info->pixels[y * info->largeur + x]) != init) return; // Pas la bonne couleur

    traite[x][y] = 1; // traité

    int voisins[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int k = 0; k < 4; ++k) {
        int vx = (x + voisins[k][0] + info->largeur) % info->largeur;
        int vy = (y + voisins[k][1] + info->hauteur) % info->hauteur;
        explorer_bloc(info, init, vx, vy, traite);
    }
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

    Point res;
    int frontiere;

    switch (d) {
        case EST: {
            for (int x = 0; x < largeur; x++) {       //on cherche la frontiere la plus a l'est
                    for (int y = 0; y < hauteur; y++) {
                        if (bloc[y][x] == 1) {
                            frontiere = x;
                        }
                    }
                }
            res.x = frontiere;
            if (b == BABORD) {
                for (int y = 0; y < hauteur; y++) {   //on cherche le pixel le plus haut sur la frontiere
                    if (bloc[y][frontiere] == 1) {
                        res.y = y;
                        break;
                    }
                }
            } 
            else {
                for (int y = 0; y < hauteur; y++) {       //on cherche le pixel le plus bas sur la frontiere (ici, on sort le break de la boucle for car on veut la derniere apparition du 1)
                    if (bloc[y][frontiere] == 1) {
                        res.y = y;
                    }
                }
            }
            break;
        }
        case SUD:
            for (int y = 0; y < hauteur; y++) {         //on cherche la frontiere la plus au sud
                    for (int x = 0; x < largeur; x++) {
                        if (bloc[y][x] == 1) {
                            frontiere = y;
                        }
                    }
                }
            res.y = frontiere;
            if (b == BABORD) {
                for (int x = 0; x < largeur; x++) {         //pixel le plus a droite sur la frontiere
                    if (bloc[frontiere][x] == 1) {
                        res.x = x;
                    }
                }
            } 
            else {
                for (int x = largeur-1; x >= 0; x--) {         //pixel le plus a gauche sur la frontiere
                    if (bloc[frontiere][x] == 1) {
                        res.x = x;
                        break;
                    }
                }
            }
            break;

        case OUEST:
            frontiere = largeur;               //on cherche la frontiere la plus a gauche
                for (int x = largeur - 1; x >= 0; x--) {
                    for (int y = 0; y < hauteur; y++) {
                        if (bloc[y][x] == 1) {
                            frontiere = x;
                        }
                    }
                }
            res.x = frontiere;
            if (b == BABORD) {
                for (int y = 0; y < hauteur; y++) {         //pixel le plus haut
                    if (bloc[y][frontiere] == 1) {
                        res.y = y;
                    }
                }
            }
            else {
                for (int y = 0; y < hauteur; y++) {         //pixel le plus bas
                    if (bloc[y][frontiere] == 1) {
                        res.y = y;
                    }
                }
            }
           break;
        
        case NORD: 
            frontiere = hauteur ;            //on cherche la frontiere la plus au nord
            for (int y = hauteur - 1; y >= 0; y--) {
                for (int x = 0; x < largeur; x++) {
                    if (bloc[y][x] == 1) {
                        frontiere = y;
                    }
                }
            }
            res.y = frontiere;
            if (b == BABORD) {
                for (int x = 0; x < largeur; x++) {     //pixel le plus a gauche
                    if (bloc[frontiere][x] == 1) {
                        res.x = x;
                        break;
                    }
                }
            }
            else {
                for (int x = 0; x < largeur; x++) {     //pixel le plus a droite
                    if (bloc[frontiere][x] == 1) {
                        res.x = x;
                    }
                }
            }
            break;
    }
   return res;
}


    
