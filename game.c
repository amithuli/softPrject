#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "solver.h"
#include "structures.h"
#include "string.h"



void fillXCells(game** board, int fill){
    /*this function will fill our empty boards with x legal values*/
    int x, y, num;
    int checkErrors();
    while (fill>0) { /*there are still *fill* cells to fill*/
        x = 1+ rand()%(*board)->dim;
        y = 1+ rand()%(*board)->dim;
        num = 1+ rand()%(*board)->dim;
        if ((*board)->playerBoard[y][x] == 0) { /*we haven't filled this cell yet*/
            (*board)->playerBoard[y][x] = num;
            if(checkErrors(**board)){ /*the value is legal*/
                fill = fill-1;
            }
            else{ /*the value is not legal, we need to return the cell's value to 0*/
                (*board)->playerBoard[y][x] = 0;
            }
        }
    }
}
/*
 * loads a puzzle from a given path
 */
int loadPuzzle(game * board, char* path, int mode){ //TODO - add free to cells before loading board + adding if no Path exists - Empty board
    int row, col, curRow, curCol;
    char c;
    FILE *toRead;
    if (strlen(path)>0){ //if there's a valid path
        toRead = fopen(path, "r+");
        if (toRead){ //copies the baord
            fscanf(toRead,"%d %d",&row,&col);
    }
    else{
            if (mode == 1){
                printf("Error: File doesn’t exist or cannot be opened\n");
                return 0;
            }
            else{ //edit mode
                printf("Error: File cannot be opened\n");
                return 0;
            }
        }
    }
    else{ //default 9x9 board
        row = 3;
        col = 3;
    }
    board->dim = (row*col);
    board->rows = row;
    board->cols = col;
    board->playerBoard = boardify(board->dim);
    board->fixedBoard = boardify(board->dim);
    board->first = 1;
    board->last = 1;
    board->previousBoard = NULL;
    board->nextBoard = NULL;
    if (strlen(path)>0){ //copying the board itself and updating fixed cells matrix
        for(curRow=0; curRow<row*col;curRow++){
            for (curCol=0; curCol<row*col; curCol++){
                fscanf(toRead,"%d%c",&(board->playerBoard[curRow][curCol]),&c);
                if (c == '.'){
                    board->fixedBoard[curRow][curCol] = 1;
                }
            }
        }
        fclose(toRead);
        return 1;
    }

}
/*
 * saves a puzzle to a given path,
 * if mode == 2 -> solve mode (no error checking)
 * if mode == 1 -> edit mode (checks errors)
 * check weather it prints another\n
 */
//TODO - board validation before saving in Edit mode
int savePuzzle(game * board, char* path, int mode){ //TODO - board validation function before for Edit mode ->this function happens after
    int curRow, curCol;
    FILE* toWrite = fopen(path,"w+");
    if (toWrite){ //checks if the file is valid for writing
        fprintf(toWrite,"%d ",board->rows);//prints the sizes
        fprintf(toWrite, "%d\n", board->cols);
        if(mode == 2){ //Solve mode
            for (curRow = 0; curRow<board->dim; curRow++){
                for (curCol=0; curCol<board->dim;curCol++){
                    fprintf(toWrite, "%d",board->playerBoard[curRow][curCol]);
                    if(board->fixedBoard[curRow][curCol]){
                        fprintf(toWrite,".");
                    }
                    if (curCol<board->dim-1){
                        fprintf(toWrite," ");
                    }
                }
                if (curCol != (board -> dim)-1){
                    fprintf(toWrite, "\r\n");
                }
            }
        }
        else{
            for (curRow = 0; curRow<board->dim; curRow++){
                for (curCol=0; curCol<board->dim;curCol++){
                    if(!board->fixedBoard[curRow][curCol] && !isLegalFinal(*board,curRow,curCol,board->playerBoard[curRow][curCol])){
                        printf("Error: board contains erroneous values\n");
                        printf("row: %d, col: %d",curRow, curCol);
                        return 0;
                    }
                    fprintf(toWrite, "%d",board->playerBoard[curRow][curCol]);
                    if(board->fixedBoard[curRow][curCol]){
                        fprintf(toWrite,".");
                    }
                    if (curCol<(board->dim)-1){
                        fprintf(toWrite," ");
                    }
                }
                if (curCol != (board->dim)-1){
                    fprintf(toWrite, "\r\n");
                }
            }
        }
        fclose(toWrite);
        printf("Saved to: %s\n", path);
        return 1;
    }
    else{
        printf("Error: File cannot be created or modified\n");
        return 0;
    }
}

