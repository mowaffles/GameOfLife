#include <stdio.h>
#include <unistd.h> 
#include <string.h>

void enterPattern(int board[24][70]){
    for (int i=0;i<24;i++){
        for (int j=0; j<70; j++){
            board[i][j] = 0;
        }
    }
    //  Initial Pattern
    board[17][22] = 1;
    board[16][23] = 1;
    board[15][24] = 1;
    board[15][25] = 1;
    board[15][26] = 1;
    board[16][26] = 1;
    board[17][26] = 1;
}

int patternDetect(int board[24][70], int boardN1[24][70], int boardN2[24][70], int boardN3[24][70]){
    int boardSize = 70 * 24 * 4;    //This size num of elements in array * size of an int data type(4 bytes) 
    if ( memcmp(board, boardN1, boardSize) == 0){ //Board to N1
        return 1;
    }
    else if ( memcmp(board, boardN2, boardSize) == 0){ //Board to N2
        return 1;
    }
    else if ( memcmp(board, boardN3, boardSize) == 0){ //Board to N3
        return 1;
    }
    else{
        OldBoardSave(board, boardN1, boardN2, boardN3, boardSize);
    }
    return 0;
}

int OldBoardSave(int board[24][70], int boardN1[24][70], int boardN2[24][70], int boardN3[24][70], int boardSize){
    memcpy(boardN3, boardN2, boardSize);
    memcpy(boardN2, boardN1, boardSize);
    memcpy(boardN1, board, boardSize);
}

void BoardtoCopy(int board[24][70], int boardCopy[24][70]){ // Copys current board into a temporary one
    int boardSize = 70 * 24 * 4; 
    memcpy(boardCopy, board, boardSize);
}

void CopyToBoard(int board[24][70], int boardCopy[24][70], int *populationNum){ // Copys state of temporary board back into a real one
    int i,j;
    *populationNum=0;
    for (i=0;i<24;i++){
        for (j=0; j<70; j++){
            board[i][j] = boardCopy[i][j];
            if (boardCopy[i][j] == 1){
                *populationNum = *populationNum+1;
            }
        }
    }
}

void ruleChecker(int x,int y, int board[24][70], int boardCopy[24][70]){  //Make all changes to a copy of board
    int neighbours = 0;
    int i,j;

    //Check num of neighbours
    for (i = -1; i < 2; i++){ //X
        for (j = -1;j < 2;j++){  //Y
            if ((x+i < 0) || (y+j < 0) || (x+i > 23) || (y+j > 69)){ //If at an edge
                continue;
            }
            if ((i == 0) && (j == 0)){ //Skip the origin
                continue;
            }
            else if(board[x+i][y+j] == 1){
                neighbours++;
            }
        }
    }

    if (neighbours == 3 ){  //Births
        boardCopy[x][y] = 1;
    }
    if ((board[x][y] == 1) && ((neighbours == 2) || (neighbours == 3))){  //Survivals
        boardCopy[x][y] = 1;
    }
    if ((neighbours >= 4) || (neighbours <= 1)){  //Deaths
        boardCopy[x][y] = 0;
    }
}

void generation(int board[24][70], int boardCopy[24][70], int *generationNum, int *populationNum){

    BoardtoCopy(board, boardCopy);
    for (int j=0; j<24; j++){ //iterate board for RuleChecker
        for (int i=0;i<70;i++){
            ruleChecker(j,i, board, boardCopy);
        }
    }
    CopyToBoard(board, boardCopy, populationNum);
    *generationNum = *generationNum+1;
}

void printBoard(int board[24][70],int *generationNum,int *populationNum){
    printf("Generation: %d         Population: %d\n", *generationNum, *populationNum);
    int i, j;
    for (j=0; j<24; j++){
        for (i=0;i<70;i++){
            if (board[j][i] == 1){
                printf("+");
            }
            else if (board[j][i] == 0){
                printf(" ");
            }
            else{ //If an error
                printf("!");
            }
        }
        printf("\n");
    }
}

int main(){
    int board[24][70];
    int boardCopy[24][70];
    int boardN1[24][70]; //Previous Board
    int boardN2[24][70]; //Previous-1 Board
    int boardN3[24][70]; //Previous-2 Board
    int generationNum = 0;
    int populationNum = 7;

    enterPattern(board);

    while (patternDetect(board, boardN1, boardN2, boardN3) == 0){
        printBoard(board, &generationNum, &populationNum);
        usleep(80000);
        generation(board, boardCopy, &generationNum, &populationNum);
        usleep(80000);
    }
    return 0;
}