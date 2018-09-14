//
// Created by Amit Huli on 13/09/2018.
//
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
/*
 * TODO - cells is the number of cells left to fill
 * stack can't be bigger than that
 */

void stackInit(Stack *S, int cells)
{
    int i = -1;
    S->size = i;
    S->data = (struct stackItem*) calloc (cells,sizeof(struct stackItem));
}

int stackIsEmpty(Stack *S){
    return (S->size == -1);
}

/*
 * pushes an element to the top of the stack
 */
void stackPush(Stack* S, int row, int col, int lastInput)
{
    S-> size++;
    S->data[S->size].row = row;
    S->data[S->size].col = col;
    S->data[S->size].lastInput = lastInput;
}

/*
 * pops an element from the stack
 */

int stackPop (Stack *S, int* params) {
    int stackIsEmpty();
    if (stackIsEmpty(S)){
        return 0;
    }
    else{
        params[0] = S->data[S->size].row;
        params[1] = S->data[S->size].col;
        params[2] = S-> data[S->size].lastInput;
        S->size--;
        return 1;
    }
}

