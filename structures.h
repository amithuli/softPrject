//
// Created by Amit Huli on 10/09/2018.
//

#ifndef SOFTWAREPROJECTFINAL_STRUCTURES_H
#define SOFTWAREPROJECTFINAL_STRUCTURES_H
typedef struct game{
    int** playerBoard;
    int** fixedBoard;
    int first;
    int last;
    struct game * nextBoard;
    struct game * previousBoard;
    int rows;
    int cols;
    int dim;
    char undo[4096];
    char redo[4096];
} game;

typedef struct Stack {
    int size;
    struct stackItem * data;
} Stack;

typedef struct stackItem {
    int row;
    int col;
    int lastInput;
} stackItem;
void stackInit(Stack *S, int cells);
int stackIsEmpty(Stack *S);
void stackPush(Stack* S, int row, int col, int lastInput);
int stackPop (Stack *S, int* params);
#endif //SOFTWAREPROJECTFINAL_STRUCTURES_H
