/*
 * board.c
 *
 *  Created on: 6 ???? 2018
 *      Author: ofeks
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "parser.h"
#include "main.h"


int** create_empty_board(int x){
	/* creates an empty x by x board and sets all values to 0*/
    int i;
    int j;
    int ** board;
    board = (int **)calloc(x, sizeof(int*));
    if (board == NULL){
		printf("Error: calloc has failed\n");
		free(board);
		return 0;
    }
	for (i = 0;i<x ; ++i){
		board[i] = (int*)calloc(x, sizeof(int));
		if (board[i] == NULL){
			printf("Error: calloc has failed\n");
			return 0;
		}
    }
	for (i=0;i<x;i++){
        for (j = 0;j<x;j++){
            board[i][j] = 0;
        }
    }
	return board;
}

int load_board(int*** game_board, int*** fixed_board, int* size, int* block_rows, int* block_cols, char* path){
	/*loads a board from a file or creates a new board*/
    int i;
    int j;
    int tempnum;
    char c;
	FILE *f;
    if (strlen(path) > 1){ // we want to load from a file
    	f = fopen(path, "r");
    	if (f){
    		fscanf(f,"%d %d",block_rows,block_cols);
    	}
		else{
			printf("Error: File cannot be created or modified\n");
			fclose(f);
			return 0;
		}
    }
    else { // we want to create a new board
        *block_rows = 3;
        *block_cols = 3;
    }
	*size = (*block_rows)*(*block_cols);
    *game_board = create_empty_board(*size);
    *fixed_board = create_empty_board(*size);
    if (strlen(path) > 1){ // taking the values from the file
		for(i=0; i<*size;i++){
			for (j=0; j<*size; j++){
				fscanf(f,"%d%c",&tempnum,&c);
				(*game_board)[i][j] = tempnum;
				if (c == '.'){
					(*fixed_board)[i][j] = (*game_board)[i][j];
				}
			}
		}
        fclose(f);
    }
	return 1;
}

int savePuzzle(game_board g_board, char* path){
    int i;
    int j;
    FILE* f;
    f = fopen(path,"w+");
    if (f){ //checks if the file is valid for writing
        fprintf(f,"%d ",g_board.block_rows);//prints the sizes
        fprintf(f, "%d\n", g_board.block_cols);
        for (i = 0; i<g_board.size; i++){
            for (j=0; j<g_board.size;j++){
                fprintf(f, "%d",g_board.game_mat[i][j]);
                if(g_board.fixed_mat[i][j] != 0){
                    fprintf(f,".");
                }
                if (j<g_board.size-1){
                    fprintf(f," ");
                }
            }
            if (j != g_board.size-1){
                fprintf(f, "\r\n");
            }
        }
        fclose(f);
        return 1;
    }
    else{
        printf("Error: File cannot be created or modified\n");
        fclose(f);
        return 0;
    }
}

void board_printer(game_board g_board){
	/*prints the board according to the format*/
	int i=0;
	int j=0;
	int pipe_counter = 0; // marks that we need to add a |
	int dash_counter = 0; // marks that we need to add a line of -
	for(i=0;i<g_board.size; i++){
		if (dash_counter == 0) { // creating a line of -
			for (j=0; j<4*g_board.size+g_board.block_cols+1;j++) {
				printf("-");
			}
			printf("\n");
			dash_counter = g_board.block_rows;
		}
		for(j=0;j<g_board.size; j++){
			if (pipe_counter == 0) { // printing a |
				printf("|");
				pipe_counter = g_board.block_cols;
			}
			if (g_board.game_mat[i][j] != 0){
				printf(" %2d",g_board.game_mat[i][j]);
			}
			else {
				printf("   ");
			}
			if(g_board.fixed_mat[i][j] != 0){
				printf(".");
			}
			else{
				printf(" ");
			}
			pipe_counter--;
		}
		printf("|\n");
		dash_counter--;
	} // adding a last line of -
	for (j=0; j<4*g_board.size+g_board.block_cols+1;j++) {
		printf("-");
	}
	printf("\n");
}
