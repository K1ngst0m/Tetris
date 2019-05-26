#include"board.h"
#include"tetris.h"

Board::Board(){
    score = 0;
    for(int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            color[i][j] = -1;
}

bool Board::judgeFull(int row){
    for(int col = 0; col < COLS; col++)
        if(color[row][col] == -1)
            return false;
    return true;
}

void Board::cleanPerRows(int i){
    for(int row = i; row > 0; row--)
        for(int col = 0; col < COLS; col++)
            color[row][col] = color[row-1][col];
       //color[row][j] = color[row+1][j];
    //for(int col = 0; col < COLS; col++)
        //color[ROWS-1][col] = -1;
}

void Board::letItGo(){
    for(int row = ROWS-1; row >= 0; row--){
        if(!judgeFull(row))
            continue;
        cleanPerRows(row);
        row++;
    }
}

bool Board::add(Tetris* block){
    for(int i = 0; i < block->SIZE; i++){
        int x = block->getX(i);
        int y = block->getY(i);

        //方块池满判断
        if (y <= 0)
            return false;
        else
            color[y][x] = block->type;
    }
    return true;
}

