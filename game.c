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

    board[5][0] = 1;
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
    int i,j;

    for (i=0;i<24;i++){
        for (j=0; j<70; j++){
            boardCopy[i][j] = board[i][j];
        }
    }

    //memcpy(boardCopy, board, sizeof (int) * 24 * 70);

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

void ruleChecker(int x,int y){  //Make all changes to a copy of board

    int neighbours = 0;
    int i,j;
    //printf("X: %d, Y: %d\n", x, y);

    //Check num of neighbours
    for (i = -1; i < 2; i++){ //X
        for (j = -1;j < 2;j++){  //Y
            if ((x+i < 0) || (y+j < 0)){
                //printf("Pass1 ");
                continue;
            }
            if ((x+i > 23) || (y+j > 69)){
                //printf("Pass2 ");
                continue;
            }
            if ((i == 0) && (j == 0)){
                //printf("Pass3 ");
                continue;
            }
            else if(board[x+i][y+j] == 1){
                //printf("Neighbour\n");
                neighbours++;
            }
        }
    }

    //printf("Neighbours: %d\n", neighbours);

    if ((neighbours == 2) || (neighbours == 3)){  //Survivals
        //printf("Survivor at %d,%d\n", x,y);
        boardCopy[x][y] = 1;
    }

    if (neighbours >= 4){  //Deaths
        //printf("Death\n");
        boardCopy[x][y] = 0;

    }

    if (neighbours == 3 ){  //Births
        //printf("Birth at %d,%d\n", x,y);
        boardCopy[x][y] = 1;
    }
}

void generation(){
    copyArrayBoard();

    for (int j=0; j<24; j++){ //iterate board for RuleChecker
        for (int i=0;i<70;i++){
            ruleChecker(j,i);
        }
    }

    copyArrayBoardCopy();
    generationNum++;
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

int main(){   

    enterPattern();

    while (patternDetect() == 0){
        printBoard();
        usleep(100000);
        generation();
        usleep(100000);
    }

    return 0;
}