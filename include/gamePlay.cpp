#include"gamePlay.h"
#include"board.h"

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
    status = INACTIVE;
    movement = NONE;
    relatLocate = new int[4][2];

    for(int i = 0; i < 4; i++) {
        relatLocate[i][0] = block_table[type][i][0];
        relatLocate[i][1] = block_table[type][i][1];
    }

}

void Tetris::rotateLeft(){
    for(int i = 0; i < SIZE; i++){
        int t = relatLocate[i][0];
        relatLocate[i][0] = -relatLocate[i][1];
        relatLocate[i][1] = t;
    }
}

void Tetris::rotateRight(){
    for(int i = 0; i < SIZE; i++){
        int t = relatLocate[i][0];
        relatLocate[i][0] = relatLocate[i][1];
        relatLocate[i][1] = -t;
    }
}

void Tetris::
