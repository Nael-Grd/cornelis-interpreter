#include "../include/pile.h"
#include <stdlib.h>


struct stack_s {
    int top;
    elem content[1000];
};


stack new() {
    struct stack_s* s = malloc(sizeof(struct stack_s));  //on alloue la memoire pour une pile
    if (s == NULL) {
        perror("Erreur d'allocation de la pile");
        exit(1);
    }
    s->top=-1;                                  
    return s;
}

int isEmpty(stack s) {
    struct stack_s * r = s;    
    return (r->top < 0);
}

void push(stack s, int e) {
    struct stack_s* r = s;
    r->top+=1;
    r->content[r->top]=e;
}

void pop(stack s) {
    if (isEmpty(s) == 0) {     
        struct stack_s* r = s;
        r->top-=1;
    }
}

void somme(stack s) {
    struct stack_s* r = s;
    if (stack_size(s) < 2) {          // necessite 2 elements dans la pile 
        int a = r->content[r->top];    
        int b = r->content[r->top-1];
        pop(s);                      
        pop(s);
        push(s, a+b);              
    }
}

void difference(stack s) {
    struct stack_s* r = s;
    if (stack_size(s) < 2) {        
        int a = r->content[r->top];    
        int b = r->content[r->top-1];
        pop(s);              
        pop(s);
        push(s, b-a);               
    }
}    

void produit(stack s) {
    struct stack_s* r = s;
    if (stack_size(s) < 2) {          
        int a = r->content[r->top];    
        int b = r->content[r->top-1];
        pop(s);                      
        pop(s);
        push(s, a*b);               
    }
}

void division(stack s) {
    struct stack_s* r = s;
    if (stack_size(s) < 2) {          
        int a = r->content[r->top];    
        int b = r->content[r->top-1];
        pop(s);                      
        pop(s);
        if (a == 0) return;
        push(s, b/a);              
    }
}

void reste(stack s) {
    struct stack_s* r = s;
    if (stack_size(s) < 2) {          
        int a = r->content[r->top];    
        int b = r->content[r->top-1];
        pop(s);                      
        pop(s);
        push(s, b%a);               
    }
}

void zero(stack s) {
    if (isEmpty(s) == 0) {     
        struct stack_s* r = s;
        int a = r->content[r->top];        
        pop(s);                       
        if (a == 0) {
            push(s, 1);     
        }
        else {
            push(s, 0);      
        }
    }
}

void plusgrand(stack s) {
    struct stack_s* r = s;
    if (stack_size(s) < 2) {       
        int a = r->content[r->top];    
        int b = r->content[r->top-1];
        pop(s);                      
        pop(s);
        if (b>a) {
            push(s, 1);   
        }
        else {
            push(s, 0);    
        }
    }
}

void duplique(stack s) {
    struct stack_s* r = s;
    if (isEmpty(s) == 0) {    
        int a = r->content[r->top];  
        pop(s);                  
        push(s, a);            
        push(s, a);
    }
}

void tourne(stack s) {
    struct stack_s* r = s;
    if (stack_size(s) < 2) {     
        int a = r->content[r->top];   // nb rotations
        int b = r->content[r->top-1];   // profondeur
        pop(s);
        pop(s);

        if (b <= 0 || stack_size(s) < b) return;
        int nb_rotations = a % b;
        if (nb_rotations < 0) nb_rotations += b;
        
        for (int i = 0; i < nb_rotations; i++) {   
            int t = r->content[r->top]; 
            for (int j = 0; j < b - 1; j++) {   
                r->content[r->top - j] = r->content[r->top - (j + 1)];  
            }
            r->content[r->top - (b - 1)] = t;  
        }
    }
}

elem peek(stack s) {
    struct stack_s* r = s;
    if (r->top < 0) return 0; // Sécurité
    return r->content[r->top];
}

int stack_size(stack s) {
    struct stack_s* r = s;
    return r->top + 1;  // top=0 signifie 1 élément
}




