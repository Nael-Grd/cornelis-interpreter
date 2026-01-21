#include "bloc.h"
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
    for (i=0; i<largeur; i++) {          //on parcours tout le tableau pour compter le nombre de 1 dedans
        for (j=0; j<hauteur; j++) {
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

    int x, y;
    for (x = 0; x < hauteur; x++) {
        for (y = 0; y < largeur; y++) {
            if (!traite[x][y]) {  //si le pixel n'a pas ete traite
                blocs++;  //on a un nouveau bloc
                couleur couleur_initiale = nom_couleur(info->pixels[x][y]);  //couleur du pixel initial du bloc
                traite[x][y] = 1;     //on marque le pixel comme traite
                
                int i, j;
                for (i = 0; i < hauteur; i++) {
                    for (j = 0; j < largeur; j++) {
                        if (!traite[i][j] && (nom_couleur(info->pixels[i][j]) == couleur_initiale)) {
                            traite[i][j] = 1;       //on marque le pixel comme traite
                        }
                    }
                }
            }
        }
    }
    return blocs;
}

int* pixel_suivant(int** bloc, direction d, bord b, int hauteur, int largeur) {
    int pixel_x ;       //coordonnees du pixel retenu
    int pixel_y ;
    int frontiere;
    switch (d) {
        case EST:
            int x, y;
            for (x = 0; x < largeur; x++) {       //on cherche la frontiere la plus a l'est
                    for (y = 0; y < hauteur; y++) {
                        if (bloc[y][x] == 1) {
                            frontiere = x;
                        }
                    }
                }
            if (b == BABORD) {
                int y;
                for (y = 0; y < hauteur; y++) {   //on cherche le pixel le plus haut sur la frontiere
                    if (bloc[y][frontiere] == 1) {
                        pixel_y = y;
                        pixel_x = frontiere;
                        break;
                    }
                }
            } 
            else {
                int y;
                for (y = 0; y < hauteur; y++) {       //on cherche le pixel le plus bas sur la frontiere (ici, on sort le break de la boucle for car on veut la derniere apparition du 1)
                    if (bloc[y][frontiere] == 1) {
                        pixel_y = y;
                        pixel_x = frontiere;
                       }
                }
            }
            break;

        case SUD:
            int x1, y1;
            for (y1 = 0; y1 < hauteur; y1++) {         //on cherche la frontiere la plus au sud
                    for (x1 = 0; x1 < largeur; x1++) {
                        if (bloc[y1][x1] == 1) {
                            frontiere = y1;
                        }
                    }
                }
            if (b == BABORD) {
                int x1;
                for (x1 = 0; x1 < largeur; x1++) {         //pixel le plus a droite sur la frontiere
                    if (bloc[frontiere][x1] == 1) {
                        pixel_y = frontiere;
                        pixel_x = x1;
                    }
                }
                break;
            } 
            else {
                int x;
                for (x = largeur; x >= 0; x--) {         //pixel le plus a gauche sur la frontiere
                    if (bloc[frontiere][x] == 1) {
                        pixel_y = frontiere;
                        pixel_x = x;
                    }
                }
                break;
            }

        case OUEST:
            frontiere = largeur - 1;               //on cherche la frontiere la plus a gauche
                int x3, y3;
                for (x3 = largeur - 1; x3 >= 0; x3--) {
                    for (y3 = 0; y3 < hauteur; y3++) {
                        if (bloc[y3][x3] == 1) {
                            frontiere = x3;
                        }
                    }
                }
            if (b == BABORD) {
                int y3;
                for (y3 = 0; y3 < hauteur; y3++) {         //pixel le plus haut
                    if (bloc[y3][frontiere] == 1) {
                        pixel_y = y3;
                        pixel_x = frontiere;
                    }
                }
                break;
            }
            else {
                int y3;
                for (y3 = 0; y3 < hauteur; y3++) {         //pixel le plus bas
                    if (bloc[y3][frontiere] == 1) {
                        pixel_y = y3;
                        pixel_x = frontiere;
                    }
                }
                break;
            }
        
        case NORD: 
            frontiere = hauteur - 1;            //on cherche la frontiere la ^plus au nord
            int x4, y4;
            for (y4 = hauteur - 1; y4 >= 0; y4--) {
                for (x4 = 0; x4 < largeur; x4++) {
                    if (bloc[y4][x4] == 1) {
                        frontiere = y4;
                    }
                }
            }
            if (b == BABORD) {
                int x4;
                for (x4 = 0; x4 < largeur; x4++) {     //pixel le plus a gauche
                    if (bloc[frontiere][x4] == 1) {
                        pixel_x = frontiere;
                        pixel_y = x4;
                        break;
                    }
                }
            }
            else {
                int x4;
                for (x4 = 0; x4 < largeur; x4++) {     //pixel le plus a droite
                    if (bloc[frontiere][x4] == 1) {
                        pixel_x = frontiere;
                        pixel_y = x4;
                    }
                }
                break;
            }
    }
    int* p=malloc(2*sizeof(int));
    p[0]=pixel_x;
    p[1]=pixel_y;
    return p;    //on retourne les coordonnees du pixel
}


    
