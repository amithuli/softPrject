//
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "structures.h"
/*
 * checks if a given string
 * contains only digits
 */
int isNumber(char* substr){
    int i = 0;
    while (substr[i] != '\0'){
        if (substr[i] < '0' || substr[i] > '9'){
            return 0;
        }
        i++;
    }
    return 1;
}
/*
 * manages the game UI and allows
 * the user to play the game
 * modes: 0 - init, 1 - solve, 2 - edit
 * markErrors: 0 - don't mark, 1 - mark
 *
 */
int playSudoku(int mode, int* markErrors, game ** gameBoard){
    char command[1024];
    char *sliced; // using fgets - get the comand
    char *todo[5]; // the command to be done
    char *path;
    return 0;
}


//
//int parser(game* game ,int gameMode){
//    char command[1024];
//    char *sliced;
//    char *finale_command[4];
//    char *location;
//    int i=0;
//    int x,y,z=0;
//    int *sizep, *colp, *rowp, ***gamep, ***fixedp;
//    int set();
//    void hint();
//    int restart();
//    int validate();
//    int win_check();
//    int load_board();
//    setbuf(stdout, NULL);
//    printf("Enter your command:\n");
//    fgets(command,1024,stdin);
//    sliced=strtok(command," \t\r\n");
//    while (sliced !=NULL && i<4){
//        finale_command[i++]=sliced;
//        sliced=strtok(NULL," \t\r\n");
//    }
//    if (strcmp(finale_command[0],"solve")==0){
//        game_board new_board;
//        if (i>1){
//            location = finale_command[1];
//            // we want to update all values of the new board by using load board function
//            sizep = &(new_board.size);
//            colp = &(new_board.block_cols);
//            rowp = &(new_board.block_rows);
//            gamep = &(new_board.game_mat);
//            fixedp = &(new_board.fixed_mat);
//            load_board(gamep, fixedp, sizep, rowp, colp, location);
//            new_board.is_first = 1;
//            new_board.is_last = 1;
//            *board = new_board;
//        }
//        return 3;
//    }
//    if (strcmp(finale_command[0],"edit")==0){
//        game_board new_board;
//        if (i>1){
//            location = finale_command[1];
//        }
//        else{
//            location = " "; // marks that we want to build a new soduko game
//        }
//        // we want to update all values of the new board by using load board function
//        sizep = &(new_board.size);
//        colp = &(new_board.block_cols);
//        rowp = &(new_board.block_rows);
//        gamep = &(new_board.game_mat);
//        fixedp = &(new_board.fixed_mat);
//        load_board(gamep, fixedp, sizep, rowp, colp, location);
//        new_board.is_first = 1;
//        new_board.is_last = 1;
//        *board = new_board;
//        return 2;
//    }
//    if ((strcmp(finale_command[0],"mark_errors")==0) && (mode == 3)){
//        if (i>1){
//            x=(int)(*finale_command[1]-'0');
//            return mode;
//        }
//    }
//    if ((strcmp(finale_command[0],"print_board")==0) && ((mode == 3) || (mode == 2))){
//        board_printer(board);
//        return mode;
//    }
//    if ((strcmp(finale_command[0],"set")==0) && ((mode == 3) || (mode == 2))){
//        if (i>3){
//            x=(int)(*finale_command[1]-'0');
//            y=(int)(*finale_command[2]-'0');
//            z=(int)(*finale_command[3]-'0');
//            set(*board,mode,x,y,z);
//            return mode;
//        }
//    }
//    if((strcmp(finale_command[0],"validate")==0) && ((mode == 3) || (mode == 2))){
//
//        return mode;
//    }
//    if ((strcmp(finale_command[0],"generate")==0) && (mode == 2)){
//
//        if (i>2){
//            x=(int)(*finale_command[1]-'0');
//            y=(int)(*finale_command[2]-'0');
//
//            return mode;
//        }
//    }
//    if((strcmp(finale_command[0],"undo")==0) && ((mode == 3) || (mode == 2))){
//
//        return mode;
//    }
//    if((strcmp(finale_command[0],"redo")==0) && ((mode == 3) || (mode == 2))){
//
//        return mode;
//    }
//    if ((strcmp(finale_command[0],"save")==0) && ((mode == 3) || (mode == 2))){
//
//        if (i>1){
//            location = finale_command[1];
//
//            return mode;
//        }
//    }
//    if ((strcmp(finale_command[0],"hint")==0 && (mode == 3))){
//
//        if (i>=2){
//            x=(int)(*finale_command[1]-'0');
//            y=(int)(*finale_command[2]-'0');
//            //hint(solved_board,y,x);
//            return mode;
//        }
//    }
//    if((strcmp(finale_command[0],"num_solutions")==0) && ((mode == 3) || (mode == 2))){
//
//        return mode;
//    }
//    if ((strcmp(finale_command[0],"auto_fill")==0) && (mode == 3)){
//
//        return mode;
//    }
//    if((strcmp(finale_command[0],"reset")==0) && ((mode == 3) || (mode == 2))){
//
//        return mode;
//    }
//    if(strcmp(finale_command[0],"exit")==0){
//        printf("Exiting...\n");
//        return 0;
//    }
//    printf("Error: invalid command\n");
//    return 1;
//}