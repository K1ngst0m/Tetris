#include"include/tetris.h"
#include"include/board.h"

const int Tetris::block_table[7][4][2] = {
    {{0, -1}, {0, 0}, {-1, 0}, {-1, 1}},    //0   Z型
    {{1, -1} ,{0, -1}, {0, 0}, {0, 1} },    //1   J型
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}   },    //2   O型
    {{-1, 0}, {0, 0}, {1, 0}, {0, 1}  },    //3   T型
    {{0, -1}, {0, 0}, {1, 0}, {1, 1}  },    //4   S型
    {{0, -1}, {0, 0}, {0, 1}, {0, 2}  },    //5   I型
    {{-1, -1}, {0, -1}, {0, 0}, {0, 1}}     //6   L型
};

Tetris::Tetris(int n_type){
    type = n_type;

    fall = false;
    speedup = false;

    status = INACTIVE;
    movement = NONE;
    relateLocate = new int[4][2];

    for(int i = 0; i < 4; i++) {
        relateLocate[i][0] = block_table[type][i][0];
        relateLocate[i][1] = block_table[type][i][1];
    }

}
void Tetris::rotateLeft() const{
    for(int i = 0; i < SIZE; i++){
        int t = relateLocate[i][0];
        relateLocate[i][0] = -relateLocate[i][1];
        relateLocate[i][1] = t;
    }
}
void Tetris::rotateRight() const{
    for(int i = 0; i < SIZE; i++){
        int t = relateLocate[i][0];
        relateLocate[i][0] = relateLocate[i][1];
        relateLocate[i][1] = -t;
    }
}

void Tetris::getShadow(Board *board, int shadow_y[]){
    int t_y = y;
    Status t_s = status;

    while(!has_landed()){
        for(int i = 0; i < SIZE; i++)
            if(getY(i) == Board::ROWS || board->color[getY(i)][getX(i)] != -1){
                lands();
                y--;
                break;
            }
        if(!has_landed())
            y++;
    }

    for(int i = 0; i < SIZE; i++)
        shadow_y[i] = getY(i);

    y = t_y;
    status = t_s;
}
