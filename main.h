/*
 * main.h
 *
 *  Created on: 6 ???? 2018
 *      Author: ofeks
 */

#ifndef MAIN_H_
#define MAIN_H_
typedef struct {
	int **game_mat;
	int **fixed_mat;
	struct game_board *next;
	struct game_board *prev;
	int size;
	int block_cols;
	int block_rows;
	int is_first;
	int is_last;
} game_board;

#endif /* MAIN_H_ */
