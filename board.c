//
// Created by Amit Huli on 09/09/2018.
//
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "structures.h"

/*
 * creates an empty board
 * with all values initialized to zero
 */
int** boardify(int size){
    int i = 0, j=0;
    int ** board;
    board = (int**) calloc(size,sizeof(int*));
    if (board == NULL){
        printf("Failed to allocate memory\n");
        return 0;
    }
    for (i; i<size; i++){
        board[i] = (int*)calloc(size,sizeof(int));
        if (board[i] == NULL){
            printf("Failed to allocate memory\n");
            for (i; i>=0;i--){
                free(board[i]);
            }
            free(board);
            return 0;
        }
        else{
            for (j=0;j<size;j++){
                board[i][j] = 0;
            }
        }
    }
    return board;
}


/*
 * prints the board
 */
void printBoard(game board, int markErrors){
    int i=0,j=0,pipes=0,dashes=0;
    for(i=0;i<board.dim; i++){
        if (dashes == 0) {
            for (j=0; j<4*board.dim+board.cols +1;j++) {
                printf("-");
            }
            printf("\n");
            dashes = board.rows;
        }
        for(j=0;j<board.dim; j++){
            if (pipes == 0) {
                printf("|");
                pipes = board.cols;
            }
            if (board.playerBoard[i][j] != 0){
                printf(" %2d",board.playerBoard[i][j]);
            }
            else {
                printf("   ");
            }
            if(board.fixedBoard[i][j] != 0){
                printf(".");
            }
            else{
                if(markErrors && board.playerBoard[i][j] != 0){
                    if (!isLegalFinal(board,i,j,board.playerBoard[i][j])){
                        printf("*");
                    }
                    else{
                        printf(" ");
                    }
                }
                else{
                    printf(" ");
                }
            }
            pipes--;
        }
        printf("|\n");
        dashes--;
    }
    for (j=0; j<4*board.dim+board.cols+1;j++) {
        printf("-");
    }
    printf("\n");
}

