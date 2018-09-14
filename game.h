//
// Created by Amit Huli on 09/09/2018.
//
#include "structures.h"
#ifndef SOFTWAREPROJECTFINAL_GAME_H
#define SOFTWAREPROJECTFINAL_GAME_H
//typedef struct game{
//    int** playerBoard;
//    int** fixedBoard;
//    int rows;
//    int cols;
//    int dim;
//} game;
int loadPuzzle(game * board, char* path,int mode);
int savePuzzle(game * board, char* path, int mode);

#endif //SOFTWAREPROJECTFINAL_GAME_H
