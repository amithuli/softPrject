/*
 * game.h
 *
 *  Created on: 12 ???? 2018
 *      Author: ofeks
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

int set(game_board board, int mode, int x, int y, int z){
	/*the function sets the value of a cell in both solve or edit modes*/
	// first we need to check that the value is in the right range
	if ((z > board.size) || (x > board.size) || (y > board.size) || (z < 0) || (x < 1) || (y < 1)) {
		printf("Error: value not in range 0-%d\n",board.size);
		return 0;
	}
	// if we are on solve mode we need to check that this is not a fixed cell
	if ((mode == 3)&&(board.game_mat[x-1][y-1] > 0)){
		printf("Error: cell is fixed\n");
		return 0;
	}
	board.game_mat[x-1][y-1] = z;
	if (mode == 2){ // if we are on edit mode we need to update the fixed cell table as well
		board.fixed_mat[x-1][y-1] = z;
	}
	return 1;
}
