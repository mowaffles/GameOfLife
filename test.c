#include <stdio.h>
#include <unistd.h> 

int board[24][70];
int boardCopy[24][70];
int generationNum = 0;

void enterPattern(){
    for (int i=0;i<24;i++){
        for (int j=0; j<70; j++){
            board[i][j] = 0;
        }
    }

    board[5][3] = 1;
    board[17][22] = 1;
    board[16][23] = 1;
    board[15][24] = 1;
    board[15][25] = 1;
    board[15][26] = 1;
    board[16][26] = 1;
    board[17][26] = 1;
}

int patternDetect(){

    return 0;
}

void copyArrayBoard(){ // Copys current board into a temporary one

/*
    int i,j;

    for (i=0;i<24;i++){
        for (j=0; j<70; j++){
            boardCopy[i][j] = board[i][j];
        }
    }
*/
    memcpy(boardCopy, board, sizeof (int) * 24 * 70);

}

void copyArrayBoardCopy(){ // Copys current board into a temporary one
    int i,j;

    for (i=0;i<24;i++){
        for (j=0; j<70; j++){
            board[i][j] = boardCopy[i][j];
        }
    }

    //memcpy(board, boardCopy, sizeof (int) * 24 * 70);

}

void printBoard(){
    printf("Generation: %d\n", generationNum);
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

void printBoardCopy(){
    printf("Generation: %d\n", generationNum);
    int i, j;
    for (j=0; j<24; j++){
        for (i=0;i<70;i++){
            if (boardCopy[j][i] == 1){
                printf("+");
            }
            else if (boardCopy[j][i] == 0){
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

    enterPattern();

    printBoard();

    copyArrayBoardCopy();

    printBoard();

    return 0;
}