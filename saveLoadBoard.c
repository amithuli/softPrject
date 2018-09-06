//
// Created by Amit Huli on 06/09/2018.
//

//TODO - BoardPrint

void initializeBoard(int** board,int r, int c){
    int row,col, i,j;
    if (row == 0){
        row = ROW;
        col = COL;
    }
    else{
        row = r;
        col = c;
    }
    for (i=0;row<row;row++){
        for (j = 0;col<col;col++){
            board[i][j] = 0;
        }
    }
}

int** boardify(int row, int col){
    int i;
    int** board;
    board = (int **) calloc(row, sizeof(int *));
    for (i=0; i<row*col;i++){
        board[i] = (int *) calloc(COL, sizeof(int));
        rowMemory(board[i]);
    }
    if (board){
        return board;
    }
    return NULL;
}

int loadPuzzle(int** gameBoard, int** fixedBoard, char* path){ //TODO - add free to cells before loading board + adding if no Path exists - Empty board
    int row, col, curRow, curCol;
    char c;
    FILE *toRead = fopen(path, "r+");
    if (toRead){
        fscanf(toRead,"%d %d",&row,&col);
        gameBoard = boardify(row,col);
        fixedBoard = boardify(row,col);
        initializeBoard(gameBoard,row,col);
        initializeBoard(fixedBoard,row,col);
        for(curRow=0; curRow<row*col;curRow++){
            for (curCol=0; curCol<row*col; curCol++){
                fscanf(toRead,"%d%c",&gameBoard[curRow][curCol],&c);
                if (c == '.'){
                    fixedBoard[curRow][curCol] = 1;
                }
            }
        }
        fclose(toRead);
        return 1;
    }
    else{
        printf("Error: File cannot be created or modified\n");
        fclose(toRead);
        return 0;
    }
}

int savePuzzle(int** gameBoard, int** fixedBoard, char* path , int blockCol, int blockRow){ //TODO - board validation function before for Edit mode ->this function happens after
    int curRow, curCol, N;
    FILE* toWrite = fopen(path,"w+");
    if (toWrite){ //checks if the file is valid for writing
        fprintf(toWrite,"%d ",blockRow);//prints the sizes
        fprintf(toWrite, "%d\n", blockCol);
        N = blockCol*blockRow;
        for (curRow = 0; curRow<N; curRow++){
            for (curCol=0; curCol<N;curCol++){
                fprintf(toWrite, "%d",gameBoard[curRow][curCol]);
                if(fixedBoard[curRow][curCol]){
                    fprintf(toWrite,".");
                }
                if (curCol<N-1){
                    fprintf(toWrite," ");
                }
            }
            if (curCol != N-1){
                fprintf(toWrite, "\r\n");
            }
        }
        fclose(toWrite);
        return 1;
    }
    else{
        printf("Error: File cannot be created or modified\n");
        fclose(toWrite);
        return 0;
    }
}

