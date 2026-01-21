#ifndef STACK_H

#define STACK_H

#define STACK_SIZE 1000000

struct stack {        //structure pour manipuler les piles defini ici pour pouvoir inclure seulement pile.h et non pile.c dans main.c
    int content[STACK_SIZE];
    int top;
};

typedef void* stack;        //type abstrait pour les piles
typedef int elem;          //type concret; on travaillera avec des piles d'entiers

/*@requires nothing
@assigns a new stack
@ensures return a new empty stack*/
stack new();

/*@requires nothing
@assigns nothing
@ensures return 1 if s is empty, 0 otherwise */
int isEmpty(stack s);

/*@requires valid adress of s, e int
@assigns *s
@ensures add e at the top of s s*/
void push(stack* s,elem e);

/*@requires valid adress of s
@assigns *s
@ensures remove the top of s */
void pop(stack* s);

//a partir de maintenant, les fonctions necessitent 2 elements dans la piles, si ce n'est pas le cas, elles seront sans effet

/*@requires valid adress of s
@assigns *s
@ensures pop two elements and add their sum at the top of s  */
void somme(stack* s);    


/*@requires valid adress of s
@assigns *s
@ensures pop two elements and add their difference at the top of s  */
void difference(stack* s);

/*@requires valid adress of s
@assigns *s
@ensures pop two elements and add their product at the top of s */
void produit(stack* s); 

/*@requires valid adress of s
@assigns *s
@ensures pop two elements and add their division at the top of s */
void division(stack* s); 

/*@requires valid adress of s
@assigns *s
@ensures pop two elements and add the remainder of the integer division of the second by the first */
void reste(stack* s);

/*@requires valid adress for s
@assigns *s
@ensures pop an element, add 1 if it is 0, 1 otherwise */
void zero(stack* s);

/*@requires valid adress of s
@assigns *s
@ensures pop two elements, add 1 if the second is larger than the first, 0 otherwise */
void plusgrand(stack* s);

/*@requires valid adress of s 
@assigns *s
@ensures pop an element and add it two times */
void duplique(stack* s);

/*@requires valid adress of s 
@assigns *s
@ensures pop two elements and make the stack turn the first element time up to the second one deep */
void tourne(stack* s);

#endif