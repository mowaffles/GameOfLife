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


        for (int i=0;i<24;i++){
        for (int j=0; j<70; j++){
            boardCopy[i][j] = 0;
        }
    }

    boardCopy[5][3] = 1;
    boardCopy[17][22] = 1;
    boardCopy[16][23] = 1;
    boardCopy[15][24] = 1;
    boardCopy[15][25] = 1;
    boardCopy[15][26] = 1;
    boardCopy[16][26] = 1;
    boardCopy[17][26] = 1;
}

int patternDetect(){
    printf("Size: %d\n", sizeof(board));
    if ( memcmp(board, boardCopy, sizeof(board)) == 0){
        printf("SUCCESS\n");
        return 1;
    }
    return 0;
}

int main(){   

    enterPattern();

    patternDetect();

    return 0;
}