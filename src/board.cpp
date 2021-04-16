#include"include/board.h"
#include"include/tetris.h"

Board::Board(){
    score = 0;
    render_score = true;
    for(auto & i : color)
        for (int & j : i)
            j = -1;
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
}

int Board::letItGo(){
    int bonusCounter = 0;
    for(int row = ROWS-1; row >= 0; row--){
        if(!judgeFull(row))
            continue;

        cleanPerRows(row);
        row++;

        add_score(1);
        bonusCounter++;
        render_score = true;
    }

    switch(bonusCounter){
        case(1):return 0;
        case(2):add_score(1);return 1;
        case(3):add_score(2);return 2;
        case(4):add_score(3);return 3;
        default: return -1;
    }
}

bool Board::add(Tetris* block){
    for(int i = 0; i < Tetris::SIZE; i++){
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

