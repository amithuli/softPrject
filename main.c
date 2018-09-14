#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "board.h"
#include "SPBufferset.h"
#include "solver.h"
#include "structures.h"
#include "Parser.h"
#include <string.h>

/*
 * TODO - modes: 0 - init, 1-edit, 2-solve
 */
int main() {
    struct game * board = (struct game*) calloc (1,sizeof(game));
//    int n;
    printf("Sudoku\n------\n");
    loadPuzzle(board,"/Users/amithu/Desktop/softwareProjectFinal/sols3.txt",2);
    printf("dim is %d\n cols are %d\n rows are %d\n isFirst %d\nisLast %d\n", board->dim, board->cols,board->rows,board->first,board->last);
    printBoard(*board,1);
//    exhaustiveBacktracking(*board);
//    printBoard(*board,0);
//    autofill(board);
//    printBoard(*board,0);
//    printf("%d is num_solutions\n",n);
//    exhaustiveBacktracking(*board);
    printf("%d\n",isNumber("0123d4"));
    printf("%d\n",strcmp("solve","sol"));
    return 0;
}