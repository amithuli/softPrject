//
// Created by Amit Huli on 09/09/2018.
//
#include "board.h"
#include "structures.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * checks weather the next step
 * is a legal step
 */
int isLegalFinal(game board, int curRow, int curCol, int input) {
    if (input == 0){
        return 1;
    }
    int i, j,rowOffset,colOffset;
    for (i=0; i<board.dim;i++) { //checks the same column
        if (i != curRow && board.playerBoard[i][curCol] == input) {
            return 0;
        }
    }
    for (i=0; i<board.dim; i++){ //checks the same row
        if (i != curCol && board.playerBoard[curRow][i] == input){
            return 0;
        }
    }
    rowOffset = board.rows * (curRow/board.rows);
    colOffset = board.cols * (curCol/board.cols); // finds the first cell in the block
    for (i = 0; i<board.rows ; i++) {
        for (j = 0 ; j<board.cols; j++) {
            if (board.playerBoard[rowOffset+i][j+colOffset] == input && (curRow != rowOffset+i || curCol != colOffset+j)) {
                return 0;
            }
        }
    }
    return 1;
}

/*
 * finds the next cell of a board
 */
void findNextCellFinal(game board , int lastRow, int lastCol, int* nextCell){
    int row = lastRow, col;
    for (col = lastCol+1; col < board.dim; col++){ // nextCell is on the same Row
        if (board.playerBoard[row][col] == 0){
            nextCell[0] = row;
            nextCell[1] = col;
            return;
        }
    }
    for (row = lastRow+1; row< board.dim; row++){
        for(col=0; col<board.dim;col++){
            if (board.playerBoard[row][col] == 0){
                nextCell[0] = row;
                nextCell[1] = col;
                return;
            }
        }
    }
}

int finished(game board){
    int row,col;
    if (board.playerBoard == NULL){
        return (0);
    }
    for (row = 0;row<board.dim;row++){
        for (col = 0;col<board.dim;col++){
            if (board.playerBoard[row][col] == 0){
                return 0;
            }
        }
    }
    return 1;
}

int countEmptyCells(game board){
    int counter = -1;
    int position[2] = {0};
    int rows, cols;
    if (board.playerBoard[0][0] == 0) {
        counter = 0;
    }
    do {
        counter++;
        rows = position[0];
        cols = position[1];
        findNextCellFinal(board,rows,cols,position);
    }
    while(position[0] != rows || position[1] != cols);
    return counter;
}

int checkErrors(game board){
    int i,j;
    for(i = 0; i<board.dim;i++){
        for (j=0; j<board.dim;j++){
            if (board.playerBoard[i][j] != 0){
                if (!isLegalFinal(board,i,j,board.playerBoard[i][j])){
                    return 0;
                }
            }
        }
    }
    return 1;
}
/*
 * returns the number of valid solutions to a given board
 * using a stack struct. if the board contains errors
 */
void exhaustiveBacktracking(game board){
    int countEmptyCells();
    void stackInit();
    int** boardify();
    int checkErrors();
    int isLegalFinal();
    void findNextCellFinal();
    int finished();
    void stackPush();
    int stackPop();
    int stackIsEmpty();
    int emptyCells = countEmptyCells(board);
    game * tmpboard;
    int i,j,top =0;
    int position[2] = {0,0};
    int checkOut[3] = {-1};
    int counter = 0;
    struct Stack * S = (Stack*) calloc(1,sizeof(Stack));
    tmpboard = (game*)calloc(1,sizeof(game));
    tmpboard->playerBoard = boardify (board.dim);
    tmpboard->dim = board.dim;
    tmpboard->rows = board.rows;
    tmpboard->cols = board.cols;
    stackInit(S,emptyCells);
    for (i = 0;i<board.dim;i++){ //copies the board
        for (j=0;j<board.dim;j++){
            tmpboard->playerBoard[i][j] = board.playerBoard[i][j];
        }
    }
    if (!checkErrors(*tmpboard)){ //no solution for board TODO - add validation of board
        printf("Error: board contains erroneous values\n");
        for (i = 0; i<board.dim;i++){
            free(tmpboard->playerBoard[i]);
        }
        free(tmpboard->playerBoard);
        free (S->data);
        free(S);
        free(tmpboard);
        return;
    }
    if(tmpboard->playerBoard[0][0] != 0) {
        findNextCellFinal(*tmpboard, 0, 0, position); //invariant - checkout, last cell backtracked to
        checkOut[0] = position[0];
        checkOut[1] = position[0];
    }
    for (top = 1; top<=tmpboard->dim;top++){
        if (isLegalFinal(*tmpboard, position[0],position[1],top)){
            tmpboard->playerBoard[position[0]][position[1]] = top;
            stackPush(S,position[0],position[1],top);
            checkOut[0] = position[0];
            checkOut[1] = position[1];
            break;
        }
        else{
            if (top == tmpboard->dim){ // no solutions
                printf("Error: board contains erroneous values\n");
                for (i = 0; i<board.dim;i++){
                    free(tmpboard->playerBoard[i]);
                }
                free(tmpboard->playerBoard);
                free (S->data);
                free(S);
                free(tmpboard);
                return;
            }
        }}
        if (finished(*tmpboard)){
            counter++;
            printf("Number of solutions: %d\n",counter);
            printf("This is a good board!\n");
            for (i = 0; i<board.dim;i++){
                free(tmpboard->playerBoard[i]);
            }
            free(tmpboard->playerBoard);
            free (S->data);
            free(S);
            free(tmpboard);
            return;
        }
        findNextCellFinal(*tmpboard,position[0],position[1],position);
    do{
            if (checkOut[0]<position[0] || checkOut[1]<position[1]){
                top = 1;
            }
            else {
                top = checkOut[2]+1;
                position[0] = checkOut[0];
                position[1] = checkOut[1];
                while (top>tmpboard->dim){
                    tmpboard->playerBoard[position[0]][position[1]] = 0;
                    stackPop(S,checkOut);
                    position[0] = checkOut[0];
                    position[1] = checkOut[1];
                    top = checkOut[2] +1;
                    tmpboard->playerBoard[position[0]][position[1]] = 0;
                    if (stackIsEmpty(S)){
                        break;
                    }
                }
            }
            for (top = top;top<=tmpboard->dim;top++){
                if (isLegalFinal(*tmpboard,position[0],position[1],top)){
                    tmpboard->playerBoard[position[0]][position[1]] = top;
                    if (finished(*tmpboard)){ //finished the board
                        counter++;
                        tmpboard->playerBoard[position[0]][position[1]] = 0;
                        stackPop(S,checkOut);
                        position[0] = checkOut[0];
                        position[1] = checkOut[1];
                        tmpboard->playerBoard[position[0]][position[1]] = 0;
                        break;
                    }
                    else{ //more cells
                        stackPush(S,position[0],position[1],top);
                        findNextCellFinal(*tmpboard,position[0],position[1],position);
                        break;
                    }
                }
                if (top == tmpboard->dim){ //backtracking
                    tmpboard->playerBoard[position[0]][position[1]] = 0;
                    stackPop(S,checkOut);
                    position[0] = checkOut[0];
                    position[1] = checkOut[1];
                    tmpboard->playerBoard[position[0]][position[1]] = 0;
                    break;
                }
            }
            if (S->size == -1 && checkOut[2] < tmpboard->dim){ //got to first element but didn't finish all options
                for (top = checkOut[2]+1;top<tmpboard->dim;top++){
                    if (isLegalFinal(*tmpboard, position[0],position[1],top)){
                        tmpboard->playerBoard[position[0]][position[1]] = top;
                        stackPush(S,position[0],position[1],top);
                        checkOut[0] = position[0];
                        checkOut[1] = position[1];
                        break;
                }
            } }
        } while(!stackIsEmpty(S));
    for (i = 0; i<board.dim;i++){
        free(tmpboard->playerBoard[i]);
    }
    free(tmpboard->playerBoard);
    free (S->data);
    free(S);
    free(tmpboard);
    printf("Number of solutions: %d\n",counter);
    if (counter == 1){
        printf("This is a good board!\n");
    }
    else {
        printf("The puzzle has more than 1 solution, try to edit it further\n");
    }
    return;
    }

    int findValid(game board, int curRow, int curCol){
    int i;
    for (i = 1; i<=board.dim;i++){
        if (isLegalFinal(board, curRow, curCol, i)) {
            return i;
        }
    }
    return 0;
}

void retRandCells(int* position,int dim){
    position[0] = 1+rand()%dim;
    position[1] = 1+ rand()%dim;
    return;
}

//struct game * fillCells(game board,int cells){
//    int countEmptyCells();
//    void stackInit();
//    int** boardify();
//    int checkErrors();
//    int isLegalFinal();
//    void findNextCellFinal();
//    int finished();
//    void stackPush();
//    int stackPop();
//    int stackIsEmpty();
//    game * tmpboard;
//    int i,j,top =0;
//    int position[2] = {0,0};
//    int checkOut[3] = {-1};
//    int counter = 0;
//    struct Stack * S = (Stack*) calloc(1,sizeof(Stack));
//    tmpboard = (game*)calloc(1,sizeof(game));
//    tmpboard->playerBoard = boardify (board.dim);
//    tmpboard->dim = board.dim;
//    tmpboard->rows = board.rows;
//    tmpboard->cols = board.cols;
//    stackInit(S,cells);
//    for (i = 0;i<board.dim;i++){ //copies the board
//        for (j=0;j<board.dim;j++){
//            tmpboard->playerBoard[i][j] = board.playerBoard[i][j];
//        }
//    }
////    if (!checkErrors(*tmpboard)){ //no solution for board TODO - add validation of board
////        for (i = 0; i<board.dim;i++){
////            free(tmpboard->playerBoard[i]);
////        }
////        free(tmpboard->playerBoard);
////        free (S->data);
////        free(S);
////        free(tmpboard);
////        return;
////    }
////    if(tmpboard->playerBoard[0][0] != 0) {
////        findNextCellFinal(*tmpboard, 0, 0, position); //invariant - checkout, last cell backtracked to
////        checkOut[0] = position[0];
////        checkOut[1] = position[0];
////    }
//    retRandCells(position,board.dim);
//    top = 1+rand()%board.dim;
//    stackPush(S,position[0],position[1],top);
//    tmpboard->playerBoard[position[0]][position[1]] = top;
//    checkOut[0] = position[0];
//    checkOut[1] = position[1];
////
////    for (top = 1; top<=tmpboard->dim;top++){
////        if (isLegalFinal(*tmpboard, position[0],position[1],top)){
////            tmpboard->playerBoard[position[0]][position[1]] = top;
////            stackPush(S,position[0],position[1],top);
////            checkOut[0] = position[0];
////            checkOut[1] = position[1];
////            break;
////        }
////        else{
////            if (top == tmpboard->dim){ // no solutions
////                printf("Error: board contains erroneous values\n");
////                for (i = 0; i<board.dim;i++){
////                    free(tmpboard->playerBoard[i]);
////                }
////                free(tmpboard->playerBoard);
////                free (S->data);
////                free(S);
////                free(tmpboard);
////                return;
////            }
////        }}
////    if (finished(*tmpboard)){
////        counter++;
////        printf("Number of solutions: %d\n",counter);
////        printf("This is a good board!\n");
////        for (i = 0; i<board.dim;i++){
////            free(tmpboard->playerBoard[i]);
////        }
////        free(tmpboard->playerBoard);
////        free (S->data);
////        free(S);
////        free(tmpboard);
////        return;
////    }
//    retRandCells(position,board.dim);
//    do{
//        if (checkOut[0]<position[0] || checkOut[1]<position[1]){
//            top = 1;
//        }
//        else {
//            top = checkOut[2]+1;
//            position[0] = checkOut[0];
//            position[1] = checkOut[1];
////            while (top>tmpboard->dim){
////                tmpboard->playerBoard[position[0]][position[1]] = 0;
////                stackPop(S,checkOut);
////                position[0] = checkOut[0];
////                position[1] = checkOut[1];
////                top = checkOut[2] +1;
////                tmpboard->playerBoard[position[0]][position[1]] = 0;
////                if (stackIsEmpty(S)){
////                    break;
////                }
////            }
//        }
//        for (cells;cells>0;cells--){
//            if (isLegalFinal(*tmpboard,position[0],position[1],1+rand()%board.dim)){
//                tmpboard->playerBoard[position[0]][position[1]] = top;
//                if (cells == 0){ //finished the board
//                    return tmpboard;
//                }
//                else{ //more cells
//                    stackPush(S,position[0],position[1],top);
//                    while(tmpboard->playerBoard[position[0]][position[1]] != 0){
//                        retRandCells(position,board.dim);
//                    }
//                    break;
//                }
//            }
//            if (top == tmpboard->dim){ //backtracking
//                tmpboard->playerBoard[position[0]][position[1]] = 0;
//                stackPop(S,checkOut);
//                position[0] = checkOut[0];
//                position[1] = checkOut[1];
//                tmpboard->playerBoard[position[0]][position[1]] = 0;
//                break;
//            }
//        }
//        if (S->size == -1 && checkOut[2] < tmpboard->dim){ //got to first element but didn't finish all options
//            for (top = checkOut[2]+1;top<tmpboard->dim;top++){
//                if (isLegalFinal(*tmpboard, position[0],position[1],top)){
//                    tmpboard->playerBoard[position[0]][position[1]] = top;
//                    stackPush(S,position[0],position[1],top);
//                    checkOut[0] = position[0];
//                    checkOut[1] = position[1];
//                    break;
//                }
//            } }
//    } while(!stackIsEmpty(S));
//    for (i = 0; i<board.dim;i++){
//        free(tmpboard->playerBoard[i]);
//    }
//    free(tmpboard->playerBoard);
//    free (S->data);
//    free(S);
//    free(tmpboard);
//    printf("Number of solutions: %d\n",counter);
//    if (counter == 1){
//        printf("This is a good board!\n");
//    }
//    else {
//        printf("The puzzle has more than 1 solution, try to edit it further\n");
//    }
//    return;
//}
/*
 * checks if a cell is "obvious" and returns
 * the "obvious" value
 */
    int checkIfSingle(game board,int curRow, int curCol){
        int i, j,rowOffset,colOffset;
        if (board.playerBoard[curRow][curCol] > 0){
            return 0;
        }
        for (i=0; i<board.dim;i++) { //checks the same column
            if (i != curRow && board.playerBoard[i][curCol] == 0) { //another cell not filled on the same col
                break;
            }
            else{
                if (i == board.dim-1){
                    return findValid(board, curRow, curCol);
                }
            }
        }
        for (i=0; i<board.dim; i++){ //checks the same row
            if (i != curCol && board.playerBoard[curRow][i] == 0){
                break;
            }
            else{
                if (i == board.dim-1){
                    return findValid(board, curRow, curCol);
                }
            }
        }
        rowOffset = board.rows * (curRow/board.rows);
        colOffset = board.cols * (curCol/board.cols); // finds the first cell in the block
        for (i = 0; i<board.rows ; i++) {
            for (j = 0 ; j<board.cols; j++) {
                if (board.playerBoard[rowOffset+i][j+colOffset] == 0 && (curRow != rowOffset+i || curCol != colOffset+j)) {
                    return 0;
                }
                else{
                    if (i == board.rows-1 && j == board.cols-1){
                        return findValid(board, curRow, curCol);
                    }
                }
            }
        }
        return 0;
}
/*
 * prints changes in the board
 */
    void printChange(int Y, int X, int Z){
        printf("Cell <%d,%d> set to %d\n",X,Y,Z);
        return;
    }
/*
 * autofills obvious cells in the board
 * uses a stack
 * TODO - add board printing after function ends +  if values need to be +1
 */
    void autofill(game* board){
    int i,j,input;
    int position[3] = {0};
    Stack *S;
    if (!checkErrors(*board)){
        printf("Error: board contains erroneous values\n");
        return;
    }
    i = board->dim*board->dim;
    S = (Stack*) calloc(1,sizeof(Stack));
    stackInit(S,i);
    for (i = 0; i<board->dim;i++){
        for (j=0;j<board->dim;j++){
            input = checkIfSingle(*board, i,j);
            if (input){
                stackPush(S,i,j,input);
                printChange(j+1,i+1,input);
            }
        }
    }
    while(!stackIsEmpty(S)){
        stackPop(S,position);
        board->playerBoard[position[0]][position[1]] = position[2];
    }
    free(S->data);
    free(S);
    }


