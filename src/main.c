#include "../include/pile.h"
#include "../include/bloc.h"
#include "../include/couleur.h"
#include "../include/lecturePPM.h"
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>

// Fonction robuste pour lire un entier (ignore les lignes vides)
void lire_entree_entier(stack s) {
    char buf[256];
    int val;
    int succes = 0;
    fprintf(stderr, ">> Entrez un entier : ");
    while (!succes) {
        if (fgets(buf, 256, stdin) == NULL) return; // Fin de fichier
        if (buf[0] == '\n' || buf[0] == '\r') continue; // Ignore lignes vides
        
        if (sscanf(buf, "%d", &val) == 1) {
            push(s, val);
            succes = 1;
        } else {
            fprintf(stderr, ">> Format invalide, reessayez un entier : ");
        }
    }
}

// Fonction robuste pour lire un caractère
void lire_entree_char(stack s) {
    char buf[256];
    char val;
    fprintf(stderr, ">> Entrez un caractere : ");
    if (fgets(buf, 256, stdin) != NULL) {
        if (sscanf(buf, "%c", &val) == 1) {
            push(s, (int)val);
        }
    }
}

// Fonction de debug 
void debug_state(int x, int y, int d, int b, int pile_sz, couleur c, int tentatives) {
    const char* dirs[] = {"EST", "SUD", "OUEST", "NORD"};
    const char* bords[] = {"BABORD", "TRIBORD"};
    fprintf(stderr, "[DBG] Pos(%3d,%3d) | %-5s | %-7s | Pile:%d | Coul:%2d | Try:%d\n", 
            x, y, dirs[d], bords[b], pile_sz, c, tentatives);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {             
        printf("Usage: %s <file>\n", argv[0]);   
        exit(1); 
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) { perror("[fopen]"); exit(1); }

    infoPPM* info = informations_PPM(file);
    stack s = new();
    int hauteur = info->hauteur, largeur = info->largeur;
    
    int** traite = malloc(hauteur * sizeof(int*));
    for (int i = 0; i < hauteur; i++) traite[i] = calloc(largeur, sizeof(int));

    direction d = EST;
    bord b = BABORD;
    
    int x_cur = 0, y_cur = 0;
    couleur c_cur = nom_couleur(info->pixels[0]);
    
    // Initialisation premier bloc
    traitement(info, c_cur, x_cur, y_cur, traite);
    
    // Premier mouvement
    Point p_sortie = pixel_suivant(traite, d, b, hauteur, largeur);
    int x_next = (p_sortie.x + (d == EST) - (d == OUEST) + largeur) % largeur;
    int y_next = (p_sortie.y + (d == SUD) - (d == NORD) + hauteur) % hauteur;
    couleur c_next = nom_couleur(info->pixels[y_next * largeur + x_next]);

    couleur c_prev = c_cur;
    int bloquants_consecutifs = 0;
    int glissement_blanc = 0; 
    Point premier_blanc = {-1, -1}; 

    while (bloquants_consecutifs < 8) { 
        debug_state(x_cur, y_cur, d, b, stack_size(s), c_prev, bloquants_consecutifs);

        // MUR (Noir / autre)
        if (c_next == autre) {
            bloquants_consecutifs++;
            
            // Ordre spec : 1. Inverse Bord, 2. Tourne Direction
            if (bloquants_consecutifs % 2 == 1) b = changer_bord(b);
            else d = changer_direction(d);
            
            // Si on vient du blanc, on pivote depuis le premier blanc rencontré
            if (glissement_blanc) p_sortie = premier_blanc;
            else p_sortie = pixel_suivant(traite, d, b, hauteur, largeur);

            x_next = (p_sortie.x + (d == EST) - (d == OUEST) + largeur) % largeur;
            y_next = (p_sortie.y + (d == SUD) - (d == NORD) + hauteur) % hauteur;
            c_next = nom_couleur(info->pixels[y_next * largeur + x_next]);
            continue; 
        }

        // BLANC (Passante)
        if (estPassante(info->pixels[y_next * largeur + x_next])) {
            bloquants_consecutifs = 0; 
            
            if (!glissement_blanc) {
                glissement_blanc = 1;
                premier_blanc.x = x_next;
                premier_blanc.y = y_next;
            }
            
            x_cur = x_next; y_cur = y_next; // Visuel
            
            // On glisse : le pivot devient le pixel blanc actuel pour avancer
            p_sortie.x = x_next;
            p_sortie.y = y_next;

            x_next = (p_sortie.x + (d == EST) - (d == OUEST) + largeur) % largeur;
            y_next = (p_sortie.y + (d == SUD) - (d == NORD) + hauteur) % hauteur;
            c_next = nom_couleur(info->pixels[y_next * largeur + x_next]);
            continue;
        }

        // COULEUR CODANTE
        bloquants_consecutifs = 0;

        if (!glissement_blanc) {
            int dif_c = dif_couleur(c_prev, c_next);
            int dif_l = dif_luminosite(c_prev, c_next);
            int a;
             switch(dif_c) {
                    case 0:
                        if (dif_l == 1) push(s, taille_bloc(traite, largeur, hauteur)); 
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
                        if (stack_size(s) >= 1 && dif_l == 2) zero(s);
                        if (stack_size(s) >= 2) {
                            if (dif_l == 0) division(s);
                            if (dif_l == 1) reste(s);
                        }
                    break;
                    case 3:
                        if (dif_l == 0 && stack_size(s) >= 2) plusgrand(s);
                        if (stack_size(s) >= 1) {
                            a = peek(s); pop(s); 
                            if (dif_l == 1) {
                                int rot = (a % 4 + 4) % 4; 
                                for (int i = 0; i < rot; i++) d = changer_direction(d); 
                            }
                            if (dif_l == 2) { 
                                int bas = (a % 2 + 2) % 2;
                                for (int i = 0; i < bas; i++) b = changer_bord(b);
                            }
                        } 
                    break;
                    case 4:
                        if (dif_l == 0 && stack_size(s) >= 1) duplique(s);
                        if (dif_l == 1 && stack_size(s) >= 2) tourne(s);
                        if (dif_l == 2) lire_entree_entier(s); 
                    break;
                    case 5:
                        if (dif_l == 0) lire_entree_char(s);
                        if (stack_size(s) >= 1) {
                            a = peek(s); pop(s);
                            if (dif_l == 1) printf("%d", a); 
                            if (dif_l == 2) printf("%c", (char)a); 
                            fflush(stdout); // force l'affichage
                        }
                    break;
                }
        }
        
        // Transition vers le nouveau bloc
        glissement_blanc = 0;
        c_prev = c_next;
        x_cur = x_next; y_cur = y_next;

        for (int i = 0; i < hauteur; i++) memset(traite[i], 0, largeur * sizeof(int));
        traitement(info, c_next, x_next, y_next, traite);

        p_sortie = pixel_suivant(traite, d, b, hauteur, largeur);
        x_next = (p_sortie.x + (d == EST) - (d == OUEST) + largeur) % largeur;
        y_next = (p_sortie.y + (d == SUD) - (d == NORD) + hauteur) % hauteur;
        c_next = nom_couleur(info->pixels[y_next * largeur + x_next]);
    }

    // Libération
    for (int i = 0; i < hauteur; i++) free(traite[i]);
    free(traite);
    free(info->pixels);
    free(info);
    fclose(file);
    return 0;
}