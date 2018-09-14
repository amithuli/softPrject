//
// Created by Amit Huli on 09/09/2018.
//
#include "game.h"
#ifndef SOFTWAREPROJECTFINAL_SOLVER_H
#define SOFTWAREPROJECTFINAL_SOLVER_H
int isLegalFinal(game board, int curRow, int curCol, int input);
void exhaustiveBacktracking(game board);
void autofill(game* board);
int checkErrors(game board);
#endif //SOFTWAREPROJECTFINAL_SOLVER_H
