#include "../include/couleur.h"

int luminance(pixel p) {
    return 0.202*(p.rouge) + 0.707*(p.vert) + 0.071*(p.bleu);   //formule de la luminance
}

int estPassante(pixel p) {
    return luminance(p) >= 128;
}

couleur nom_couleur(pixel p) {
    // On définit des seuils pour accepter de légères variations
    int r = p.rouge, v = p.vert, b = p.bleu;

    // CLAIR (255, 128, 128)
    if (r > 200 && v > 100 && v < 150 && b > 100 && b < 150) return rouge_clair;
    if (r > 200 && v > 200 && b > 100 && b < 150) return jaune_clair;
    if (r > 100 && r < 150 && v > 200 && b > 100 && b < 150) return vert_clair;
    if (r > 100 && r < 150 && v > 200 && b > 200) return cyan_clair;
    if (r > 100 && r < 150 && v > 100 && v < 150 && b > 200) return bleu_clair;
    if (r > 200 && v > 100 && v < 150 && b > 200) return magenta_clair;

    // NORMAL (255, 0, 0)
    if (r > 200 && v < 50 && b < 50) return rouge_normal;
    if (r > 200 && v > 200 && b < 50) return jaune_normal;
    if (r < 50 && v > 200 && b < 50) return vert_normal;
    if (r < 50 && v > 200 && b > 200) return cyan_normal;
    if (r < 50 && v < 50 && b > 200) return bleu_normal;
    if (r > 200 && v < 50 && b > 200) return magenta_normal;

    // FONCÉ (128, 0, 0)
    if (r > 100 && r < 150 && v < 50 && b < 50) return rouge_fonce;
    if (r > 100 && r < 150 && v > 100 && v < 150 && b < 50) return jaune_fonce;
    if (r < 50 && v > 100 && v < 150 && b < 50) return vert_fonce;
    if (r < 50 && v > 100 && v < 150 && b > 100 && b < 150) return cyan_fonce;
    if (r < 50 && v < 50 && b > 100 && b < 150) return bleu_fonce;
    if (r > 100 && r < 150 && v < 50 && b > 100 && b < 150) return magenta_fonce;

    return autre; 
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
    int luminosite1 = -1, luminosite2 = -1;
    switch (c1) {
        case rouge_clair:
        case jaune_clair:
        case vert_clair:
        case cyan_clair:
        case bleu_clair:
        case magenta_clair:
            luminosite1 = 0;  // on numerote 0 la lumonosite claire
            break;
        case rouge_normal:
        case jaune_normal:
        case vert_normal:
        case cyan_normal:
        case bleu_normal:
        case magenta_normal:
            luminosite1 = 1;  // on numerote 1 la lumonosite normale
            break;
        case rouge_fonce:
        case jaune_fonce:
        case vert_fonce:
        case cyan_fonce:
        case bleu_fonce:
        case magenta_fonce:
            luminosite1 = 2;  // on numerote 2 la lumonosite foncee
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
            luminosite2 = 0;  
            break;
        case rouge_normal:
        case jaune_normal:
        case vert_normal:
        case cyan_normal:
        case bleu_normal:
        case magenta_normal:
            luminosite2 = 1;  
            break;
        case rouge_fonce:
        case jaune_fonce:
        case vert_fonce:
        case cyan_fonce:
        case bleu_fonce:
        case magenta_fonce:
            luminosite2 = 2;  
            break;
        default:
            return -1;  
    }
    if (luminosite1 != -1 && luminosite2 != -1) {
        int dif = luminosite2 - luminosite1;
        while (dif < 0) dif += 3; 
        return dif % 3;
    }
    return -1;
}
