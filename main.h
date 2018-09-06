#ifndef MAIN_H_
#define MAIN_H_
typedef struct {
	int **game_mat;
	int **fixed_mat;
	struct game_board *next;
	struct game_board *prev;
	int cols;
	int rows;
	int block_cols;
	int block_rows;
} game_board;

#endif /* MAIN_H_ */
