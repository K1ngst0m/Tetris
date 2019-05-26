
#ifndef _BOARD_H
#define _BOARD_H

#include"tetris.h"
class Board{ //方块池/游戏边界

public:
    static const int WINDOW_WIDTH = 300;//宽度
    static const int WINDOW_HEIGHT = 600;//高度

    static const int ROWS = 30; //行数
    static const int COLS = 15; //列数

    static const int HEI_PER_BLOCK = WINDOW_HEIGHT / COLS; //单行高度
    static const int WTH_PER_BLOCK = WINDOW_WIDTH / ROWS;  //单列高度
    //static const int BONUS = 3;

    int color[ROWS][COLS];     //二维数组表示方块坐标
    bool render_score = 1;

    Board();                   //方块池初始化: 分数=0, 方块池清空

    void add_score(int add){score += add;}
    void letItGo();                             //消除且计分
    int getScore(){return score;}               //获取分数
    bool add(Tetris* block);               //方块堆叠

private:
    int score;

    bool judgeFull(int row); //判断是否满行, 是返回true, 否返回false
    void cleanPerRows(int row); //清除行
};

#endif
