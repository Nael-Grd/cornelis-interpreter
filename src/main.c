#include "../include/pile.h"
#include "../include/bloc.h"
#include "../include/couleur.h"
#include "../include/lecturePPM.h"
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
    if (argc != 2) {             
        printf("Usage: %s <file>\n", argv[0]);   
        exit(1); 
    }

    FILE* file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("[fopen]");
            exit(1);        
        }

    infoPPM* info = informations_PPM(file); //on recupere les infos du fichier (largeur, hauteur, couleuMax, pixels)

    stack s = new();     //initialisation de la pile d'actions
    int hauteur = info->hauteur, largeur = info->largeur;         //pour faciliter la manipulation
    int** traite = malloc(hauteur * sizeof(int*)); // On crée les lignes
    for (int i = 0; i < hauteur; i++) {
        traite[i] = calloc(largeur, sizeof(int));  // On crée les colonnes (calloc met à 0)
    }

    //Conditions initiales                   
    direction d = EST;
    bord b = BABORD;

    couleur c_depart = nom_couleur(info->pixels[0]); // y=0, x=0 donc indice 0
    int** bloc_courant = traitement(info, c_depart, 0, 0, traite);
    
    Point p_prev = {0, 0}; 
    couleur c_prev = c_depart;

    Point p_sortie = pixel_suivant(bloc_courant, d, b, hauteur, largeur);

    Point p_cur;
    p_cur.x = (p_sortie.x + (d == EST) - (d == OUEST) + largeur) % largeur;
    p_cur.y = (p_sortie.y + (d == SUD) - (d == NORD) + hauteur) % hauteur;
    couleur c_cur = nom_couleur(info->pixels[p_cur.y * largeur + p_cur.x]);    //correspondent aux couleurs du precedent bloc et celui sur lequel on est pour pouvoir faire les comparaisons

    int bloquants_consecutifs = 0;    //pour pouvoir alterner changement de direction et bord
    int blocs_traites = 0;
    int nb_blocs = nombre_blocs(info, traite);

    while (blocs_traites < nb_blocs)    {    

        if (nom_couleur(info->pixels[p_cur.y * largeur + p_cur.x]) == autre) {      // si le pixel est une couleur bloquante
            bloquants_consecutifs += 1;
        if (bloquants_consecutifs %2 == 1) { d = changer_direction(d); }
        else { b = changer_bord(b); }

        Point p_sortie = pixel_suivant(bloc_courant, d, b, hauteur, largeur);

        p_cur.x = (p_sortie.x + (d == EST) - (d == OUEST) + largeur) % largeur;
        p_cur.y = (p_sortie.y + (d == SUD) - (d == NORD) + hauteur) % hauteur;
        c_cur = nom_couleur(info->pixels[p_cur.y * largeur + p_cur.x]);
        }
     
        if (estPassante(info->pixels[p_cur.y * largeur + p_cur.x])) {
            while (estPassante(info->pixels[p_cur.y * largeur + p_cur.x])) {     
                p_cur.x = (p_cur.x + (d == EST) - (d == OUEST) + largeur) % largeur;
                p_cur.y = (p_cur.y + (d == SUD) - (d == NORD) + hauteur) % hauteur;
            }
            c_cur = nom_couleur(info->pixels[p_cur.y * largeur + p_cur.x]);
            bloquants_consecutifs = 0; 
        }

        else {          // couleur codante
            int dif_c = dif_couleur(c_prev, c_cur);
            int dif_l = dif_luminosite(c_prev, c_cur);          // en fonction des differences de couleur et luminosite on effectuera des actions sur la pile
            int a;                            //va nous servir a stocker le top de la pile d'actions
            switch(dif_c) {
                case 0:
                    if (dif_l == 1) push(s, taille_bloc(bloc_courant, largeur, hauteur));
                    if (dif_l == 2 && stack_size(s) >= 1) pop(s);
                break;
                case 1:
                    if (stack_size(s) >= 2) {
                        if (dif_l == 0) somme(s);
                        if (dif_l == 1) difference(s);
                        if (dif_l == 2) produit(s);
                    }
                break;
                case 2:
                    if (stack_size(s) >= 1 && dif_l == 2) zero(s); // un seul élément suffit pour Not
                    if (stack_size(s) >= 2) {
                        if (dif_l == 0) division(s);
                        if (dif_l == 1) reste(s);
                    }
                break;
                case 3:
                    if (dif_l == 0 && stack_size(s) >= 2) plusgrand(s);
                    if (stack_size(s) >= 1) {
                        a = peek(s);
                        if (dif_l == 1) {
                            for (int i = 0; i < a; i++) d = changer_direction(d); 
                        }
                    if (dif_l == 2) {
                        for (int i = 0; i < a; i++) b = changer_bord(b);
                    }
                    } 
                break;
                case 4:
                    if (dif_l == 0 && stack_size(s) >= 1) duplique(s);
                    if (dif_l == 1 && stack_size(s) >= 2) tourne(s);
                    if (dif_l == 2) {
                        int val;
                        printf("Veuillez entrer un entier : ");
                        if(scanf("%d", &val) == 1) push(s, val);
                    }
                break;
                case 5:
                    if (dif_l == 0) {
                        char car;
                        printf("Entrer un caractère : ");
                        if(scanf(" %c", &car) == 1) push(s, (int)car);
                    }
                    if (stack_size(s) >= 1) {
                        a = peek(s);
                        if (dif_l == 1) printf("%d\n", a);
                        if (dif_l == 2) printf("%c", (char)a);
                    }
                break;
            }

            c_prev = c_cur;
            p_prev = p_cur; 

            for (int i = 0; i < hauteur; i++) {
                for (int j = 0; j < largeur; j++) traite[i][j] = 0;
            }

            traitement(info, c_prev, p_prev.x, p_prev.y, traite);
            Point p_sortie = pixel_suivant(traite, d, b, hauteur, largeur);
            p_cur.x = (p_sortie.x + (d == EST) - (d == OUEST) + largeur) % largeur;
            p_cur.y = (p_sortie.y + (d == SUD) - (d == NORD) + hauteur) % hauteur;
            c_cur = nom_couleur(info->pixels[p_cur.y * largeur + p_cur.x]);

            bloquants_consecutifs = 0;
            blocs_traites += 1; 
        }
    }
    fclose(file);
    return 0;
}
