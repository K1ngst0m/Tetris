#include"board.h"

Board::Board(){
    score = 0;
    for(int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            color[i][j] = -1;
}

bool Board::judgeFull(int i){
    for(int j = 0; j < COLS; j++)
        if(color[i][j] == -1)
            return false;
    return true;
}

void Board::cleanPerRows(int row){
    for(int j = 0; j < COLS; j++)
       color[row][j] = color[row+1][j];

    for(int col = 0; col < COLS; col++)
        color[ROWS-1][col] = -1;
}

void Board::letItGo(){
    for(int row = 0; row < ROWS; row++)
        if(judgeFull(row))
            cleanPerRows(row);
}

