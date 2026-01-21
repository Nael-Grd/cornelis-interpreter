#include "couleur.h"

int luminance(pixel p) {
    return 0.202*(p.rouge) + 0.707*(p.vert) + 0.071*(p.bleu);   //formule de la luminance
}

int estPassante(pixel p) {
    return luminance(p) >= 128;
}

couleur nom_couleur(pixel p) {
    if (p.rouge == 255 && p.vert == 128 && p.bleu == 128) {
        return rouge_clair;
    } else if (p.rouge == 255 && p.vert == 255 && p.bleu == 128) {
        return jaune_clair;
    } else if (p.rouge == 128 && p.vert == 255 && p.bleu == 128) {
        return vert_clair;
    } else if (p.rouge == 128 && p.vert == 255 && p.bleu == 255) {
        return cyan_clair;
    } else if (p.rouge == 128 && p.vert == 128 && p.bleu == 255) {
        return bleu_clair;
    } else if (p.rouge == 255 && p.vert == 128 && p.bleu == 255) {
        return magenta_clair;
    } else if (p.rouge == 255 && p.vert == 0 && p.bleu == 0) {
        return rouge_normal;
    } else if (p.rouge == 255 && p.vert == 255 && p.bleu == 0) {
        return jaune_normal;
    } else if (p.rouge == 0 && p.vert == 255 && p.bleu == 0) {
        return vert_normal;
    } else if (p.rouge == 0 && p.vert == 255 && p.bleu == 255) {
        return cyan_normal;
    } else if (p.rouge == 0 && p.vert == 0 && p.bleu == 255) {
        return bleu_normal;
    } else if (p.rouge == 255 && p.vert == 0 && p.bleu == 255) {
        return magenta_normal;
    } else if (p.rouge == 128 && p.vert == 0 && p.bleu == 0) {
        return rouge_fonce;
    } else if (p.rouge == 128 && p.vert == 128 && p.bleu == 0) {
        return jaune_fonce;
    } else if (p.rouge == 0 && p.vert == 128 && p.bleu == 0) {
        return vert_fonce;
    } else if (p.rouge == 0 && p.vert == 128 && p.bleu == 128) {
        return cyan_fonce;
    } else if (p.rouge == 0 && p.vert == 0 && p.bleu == 128) {
        return bleu_fonce;
    } else if (p.rouge == 128 && p.vert == 0 && p.bleu == 128) {
        return magenta_fonce;
    } else {
        return autre;    //cas couleur non codante
    }
}

int dif_couleur(couleur c1,couleur c2) {
    couleur cycle[3][6] = {{rouge_clair, jaune_clair, vert_clair, cyan_clair, bleu_clair, magenta_clair},       //tableau des couleurs avec le meme 2nd indice pour les memes couleurs
                           {rouge_normal, jaune_normal, vert_normal, cyan_normal, bleu_normal, magenta_normal},
                           {rouge_fonce, jaune_fonce, vert_fonce, cyan_fonce, bleu_fonce, magenta_fonce}};

    int indice1=-1, indice2=-1;   // on va chercher le 2nd indice de chaque couleur
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<6; j++) {
            if (c1==cycle[i][j]) 
                indice1=j;
            if (c2==cycle[i][j])
                indice2=j;
        }
    }
    if (indice1 != -1 && indice2 != -1) {    // si les 2 couleurs sont codantes
        int dif = indice2 - indice1;
        if (dif < 0) {
            dif += 6;      // attention si difference negative car onparcours le cycle de gauche vers droite
        }
        return dif;
    }
    return -1;     
}   

int dif_luminosite(couleur c1, couleur c2) {
    int luminosite1=0, luminosite2=0;
    switch (c1) {
        case rouge_clair:
        case jaune_clair:
        case vert_clair:
        case cyan_clair:
        case bleu_clair:
        case magenta_clair:
            luminosite1 = 1;  // on numerote 1 la lumonosite claire
            break;
        case rouge_normal:
        case jaune_normal:
        case vert_normal:
        case cyan_normal:
        case bleu_normal:
        case magenta_normal:
            luminosite1 = 2;  // on numerote 2 la lumonosite normale
            break;
        case rouge_fonce:
        case jaune_fonce:
        case vert_fonce:
        case cyan_fonce:
        case bleu_fonce:
        case magenta_fonce:
            luminosite1 = 3;  // on numerote 3 la lumonosite foncee
            break;
        default:
            return -1;  // cas couleur non codante, on s'arret la
    }

    switch (c2) {               // de meme que pour c1
        case rouge_clair:
        case jaune_clair:
        case vert_clair:
        case cyan_clair:
        case bleu_clair:
        case magenta_clair:
            luminosite2 = 1;  
            break;
        case rouge_normal:
        case jaune_normal:
        case vert_normal:
        case cyan_normal:
        case bleu_normal:
        case magenta_normal:
            luminosite2 = 2;  
            break;
        case rouge_fonce:
        case jaune_fonce:
        case vert_fonce:
        case cyan_fonce:
        case bleu_fonce:
        case magenta_fonce:
            luminosite2 = 3;  
            break;
        default:
            return -1;  
    }
    int dif=luminosite2-luminosite1;
    if (dif < 0) {
        dif += 3;  // 3 etant la taille du cycle et comme on parcours le cycle de gauche a droite
    }
    return dif;
}
