/*
 * main.c

 *
 *  Created on: 12 ???? 2018
 *      Author: ofeks
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "parser.h"
#include "main.h"
int main(int argc, char *argv[]) {
	int mode = 1;
	game_board fake_board;
	game_board *board;
	int set_fixed();
	int build_rand_mat();
	void game_status();
	void build_fixed_and_board();
	int menu();
	void board_printer();
	setbuf(stdout, NULL);
	printf("Sudoku\n------\n");
	fake_board.size = 0; // marks that this is an empty board and not a real one
	board = &fake_board;
	while (mode != 0) {
		mode = menu(mode,board);
		board_printer(*board);
	}
	return 0;
}

