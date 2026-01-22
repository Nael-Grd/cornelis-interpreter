#include "../include/pile.h"
#include <stdlib.h>

typedef struct stack_s *stack;

stack new() {
    struct stack_s* s = malloc(sizeof(struct stack_s));  //on alloue la memoire pour une pile
    if (s == NULL) {
        perror("Erreur d'allocation de la pile");
        exit(EXIT_FAILURE);
    }
    s->top=-1;                                  
    return (stack)s;
}

int isEmpty(stack s) {
    struct stack_s * r = s;    
    return (r->top < 0);
}

void push(stack s,elem e) {
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
    if (r->top >= 1) {          // necessite 2 elements dans la pile 
        int a = r->content[r->top];    
        int b = r->content[r->top-1];
        pop(s);                      
        pop(s);
        push(s, a+b);              
    }
}

void difference(stack s) {
    struct stack_s* r = s;
    if (r->top >= 1) {        
        int a = r->content[r->top];    
        int b = r->content[r->top-1];
        pop(s);              
        pop(s);
        push(s, b-a);               
    }
}    

void produit(stack s) {
    struct stack_s* r = s;
    if (r->top >= 1) {          
        int a = r->content[r->top];    
        int b = r->content[r->top-1];
        pop(s);                      
        pop(s);
        push(s, a*b);               
    }
}

void division(stack s) {
    struct stack_s* r = s;
    if (r->top >= 1) {          
        int a = r->content[r->top];    
        int b = r->content[r->top-1];
        pop(s);                      
        pop(s);
        push(s, b/a);              
    }
}

void reste(stack s) {
    struct stack_s* r = s;
    if (r->top >= 1) {          
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
    if (r->top >= 1) {       
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
    if (r->top >= 1) {     
        int a = r->content[r->top];     
        int b = r->content[r->top-1];   
        pop(s);
        pop(s);
    
        if (r->top >= a - 1 && a > 0) {     
            for (int i = 0; i < b; i++) {   
                int t = r->content[r->top]; 
                for (int j = 0; j < a - 1; j++) {   
                    r->content[r->top - j] = r->content[r->top - (j + 1)];  
                }
                r->content[r->top - (a - 1)] = t;  
            }
        }
    }
}





