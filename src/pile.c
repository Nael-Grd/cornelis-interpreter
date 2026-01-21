#include "pile.h"
#include <stdlib.h>

stack new() {
    struct stack* s=malloc(sizeof(struct stack));  //on alloue la memoire pour une pile
    s->top=-1;                                  //qui sera vide
    return s;
}

int isEmpty(stack s) {
    struct stack* r=s;     //necesaire pour pouvoir travaille avec le type struct stack concret
    return (r->top < 0);
}

void push(stack* s,elem e) {
    struct stack* r=*s;
    r->top+=1;
    r->content[r->top]=e;
}

void pop(stack* s) {
    if (isEmpty(s) == 0) {     //si la pile est non vide
        struct stack* r=*s;
        r->top-=1;
    }
}

void somme(stack* s) {
    struct stack* r=*s;
    if (r->top >= 1) {        //si la pile a au moins 2 elements
        int a=r->content[r->top];    //on stock nos 2 elements
        int b=r->content[r->top-1];
        pop(s);                      //on depile 2 fois
        pop(s);
        push(s, a+b);               //on empile la somme
    }
}

void difference(stack* s) {
    struct stack* r=*s;
    if (r->top >= 1) {        
        int a=r->content[r->top];    
        int b=r->content[r->top-1];
        pop(s);              
        pop(s);
        push(s, b-a);               //on empile la difference (attention, second-premier)
    }
}    

void produit(stack* s) {
    struct stack* r=*s;
    if (r->top >= 1) {          
        int a=r->content[r->top];    
        int b=r->content[r->top-1];
        pop(s);                      
        pop(s);
        push(s, a*b);               //on empile le produit
    }
}

void division(stack* s) {
    struct stack* r=*s;
    if (r->top >= 1) {          
        int a=r->content[r->top];    
        int b=r->content[r->top-1];
        pop(s);                      
        pop(s);
        push(s, b/a);               //on empile le quotient (second/premier)
    }
}

void reste(stack* s) {
    struct stack* r=*s;
    if (r->top >= 1) {          
        int a=r->content[r->top];    
        int b=r->content[r->top-1];
        pop(s);                      
        pop(s);
        push(s, b%a);               //on empile le reste de la division (second par premier)
    }
}

void zero(stack* s) {
    if (isEmpty(s) == 0) {     //si la pile est non vide
        struct stack* r=*s;
        int a=r->content[r->top];        //on stock l'element
        pop(s);                         //puis on le depile
        if (a==0) {
            push(s, 1);     //on empile 1 si il vaut 0...
        }
        else {
            push(s, 0);        //...et 0 sinon
        }
    }
}

void plusgrand(stack* s) {
    struct stack* r=*s;
    if (r->top >= 1) {       // on depile 2 elements
        int a=r->content[r->top];    
        int b=r->content[r->top-1];
        pop(s);                      
        pop(s);
        if (b>a) {
            push(s, 1);   //on empile 1 si le second est plus grand...
        }
        else {
            push(s, 0);    //...et 0 sinon
        }
    }
}

void duplique(stack* s) {
    struct stack* r=*s;
    if (isEmpty(s) == 0) {    //si la pile est non vide
        int a=r->content[r->top];   //on stock notre element
        pop(s);                  //on le depile
        push(s, a);            //puis le rempile 2 fois
        push(s, a);
    }
}

void tourne(stack* s) {
    struct stack* r=*s;
    if (r->top >= 1) {       //si il y a au moins 2 elements
        int a=r->content[r->top];    
        int b=r->content[r->top-1];
        pop(s);
        pop(s);
        if (r->top >= a-1) {     //on verifie si il y a assez de profondeur dans la pile
            int i;
            int t;
            for (i=0; i<b; i++) {   //on va faire tourner b fois
                t=r->content[r->top];   //on stock la valeur a faire tourner qui s'actualisera a chaque itteration
                int j;          
                for (j=0; j<a; j++) {   //on fait tourner a la profondeur a
                    r->content[r->top -j]=r->content[r->top -(j+1)];  //on decale
                }
                r->content[r->top -a]=t;   //on remplace le dernier
            }
        }
    }
}





