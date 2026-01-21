#include "pile.h"
#include "bloc.h"
#include "couleur.h"
#include "lecturePPM.h"
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
    if (argc != 2) {             
        printf("Usage: %s <file>\n", argv[0]);   
        exit(0); 
    }

    FILE* file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("[fopen]");
            exit(1);        
        }
    infoPPM* info = informations_PPM(file); //on recupere les infos du fichier (largeur, hauteur, couleuMax, pixels)

    stack s = new();     //initialisation de la pile d'actions
    struct stack*r = s;       //comme ca on pourra manipuler r->content et r->top
    int hauteur=info->hauteur, largeur=info->largeur;         //pour faciliter la manipulation
    int** traite = malloc(largeur*hauteur*sizeof(int));
    memset(traite, 0, largeur*hauteur*sizeof(int));

//Conditions initiales                   
    direction d=EST;
    bord b=BABORD;

    int** bloc_courant=traitement(info, nom_couleur(info->pixels[0][0]), 0, 0, traite);  //bloc en haut a gauche   
    int p_prev[2]={0,0};        //coord des pixels precedent et celui sur lequel on est pour pouvoir revenir sur l'ancien si on tombe sur une couleur bloquante
    int* p_cur=pixel_suivant(bloc_courant, d, b, hauteur, largeur);
    couleur c_prev = nom_couleur(info->pixels[p_prev[0]][p_prev[1]]);             
    couleur c_cur = nom_couleur(info->pixels[p_cur[0]][p_cur[1]]);                                    //correspondent aux couleurs du precedent bloc et celui sur lequel on est pour pouvoir faire les comparaisons

    int bloquants_consecutifs = 0;    //pour pouvoir alterner changement de direction et bord
    int blocs_traites = 0;
    int nb_blocs = nombre_blocs(info, traite);

    while (blocs_traites < nb_blocs)    {                         //tant que tous les blocs n'ont pas ete traites {
       if (!estPassante(info->pixels[p_cur[0]][p_cur[1]])) {      //si le pixel est une couleur bloquante
            bloquants_consecutifs += 1;
            if (bloquants_consecutifs %2 == 1)      //on change de maniere alternee le bord et la direction
                changer_direction(d);
            else
                changer_bord(b);
            p_cur=pixel_suivant(bloc_courant, d, b, hauteur, largeur);   //on a donc un nouveau pixel suivant

        }

     
        if (estPassante(info->pixels[p_cur[0]][p_cur[1]])) {     //si c'est une couleur passante
            switch(d) {
                case EST:
                    while (estPassante(info->pixels[p_cur[0]][p_cur[1]])) 
                        p_cur[0] += 1;            //on decale a droite notre pixel courant
                    break;
                case SUD:
                    while (estPassante(info->pixels[p_cur[0]][p_cur[1]])) 
                        p_cur[1] -= 1;            //on monte notre pixel courant
                    break;
                case OUEST:
                    while (estPassante(info->pixels[p_cur[0]][p_cur[1]])) 
                        p_cur[0] -= 1;             //on decale a gauche
                    break; 
                case NORD:
                    while (estPassante(info->pixels[p_cur[0]][p_cur[1]])) 
                        p_cur[1] += 1;                //on decale a droite
                    break;
            }
            bloquants_consecutifs = 0;    //on remet le conteur a 0 car on est plus sur un bloquant
        } 

        else {          //c'est une couleur codante
            int dif_c = dif_couleur(c_prev, c_cur);
            int dif_l = dif_luminosite(c_prev, c_cur);          //en fonction des differences de couleur et luminosite on effectuera des actions sur la pile
            int a;   //va nous servir a stocker le top de la pile d'actions
            switch(dif_c) {
                case 0:
                    if (dif_l == 1)
                        push(&s, taille_bloc(bloc_courant, largeur, hauteur));
                    if (dif_l == 2)
                        pop(&s);
                break;
                case 1:
                    if (dif_l == 0)
                        somme(&s);
                    if (dif_l == 1)
                        difference(&s);
                    if (dif_l == 2)
                        produit(&s);
                break;
                case 2:
                    if (dif_l == 0)
                        division(&s);
                    if (dif_l == 1)
                        reste(&s);
                    if (dif_l == 2)
                        zero(&s);
                break;
                case 3:
                    if (dif_l == 0)
                        plusgrand(&s);
                    if (dif_l == 1) {
                        a=r->content[r->top];    //on sotck l'element au dessus de la pile
                        pop(&s);
                        int i;
                        for (i=0; i<a; i++)     //on change de direction autant de fois que cet element 
                            changer_direction(d);
                    }
                    if (dif_l == 2) {
                        a=r->content[r->top];
                        pop(&s);
                        int i;
                        for (i=0; i<a; i++)      //on change de bord autant de fois que l'element au debut de la pile
                            changer_direction(d);
                    }  
                    break;
                case 4:
                    if (dif_l == 0)
                        duplique(&s);
                    if (dif_l == 1)
                        tourne(&s);
                    int b;
                    if (dif_l == 2) {
                        printf("Veuillez entrer un entier : ");
                        scanf("%d", &b);
                        push(&s, b);
                    }
                break;
                case 5: 
                    char c;
                    if (dif_l == 0) {
                        printf("Veillez entrer un caractère : ");
                        scanf("%c", &c);
                        push(&s, (int)c);
                    }
                    if (dif_l == 1) {    
                        a=r->content[r->top];
                        pop(&s);
                        printf("%d\n", a);            //on depile un element et on l'affiche
                    }  
                    if (dif_l == 2) {  
                        
                        a=r->content[r->top];pop(&s);
                        printf("%c\n", (char)a);            //on depile un element et on le caractere correspondant au code ASCII
                    }
                break;
            }
            bloc_courant = traitement(info, c_cur, p_cur[0], p_cur[1], traite);  //on assigne le nouveau bloc
            memcpy(p_prev, p_cur, 2*sizeof(int));    //on garde le pixel du bloc precedent
            p_cur=pixel_suivant(bloc_courant, d, b, hauteur, largeur);  //pixel pour la suite
            bloquants_consecutifs = 0;    //on reinitialise le conteur car on est plus sur des bloquants
            blocs_traites += 1;
        }
    }
    fclose(file);
    return 0;
}
