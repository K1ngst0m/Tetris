//方块池类, 定义方块池边框大小, 每格方块大小
#ifndef SRC_BOARD_H_
#define SRC_BOARD_H_


#include"tetris.h"
class Board{
public:
    static const int WINDOW_WIDTH = 300;//宽度
    static const int WINDOW_HEIGHT = 600;//高度

    static const int ROWS = 30; //行数
    static const int COLS = 15; //列数

    static const int HEI_PER_BLOCK = WINDOW_HEIGHT / ROWS; //单行宽度
    static const int WTH_PER_BLOCK = WINDOW_WIDTH / COLS;  //单列高度
    static const int BONUS = 3; //分数相关

    int color[ROWS][COLS];                      //二维数组表示方块坐标
    bool render_score;                          //刷新分数

    Board();                                    //方块池初始化: 分数=0, 方块池清空

    void add_score(int add){score += add;}      //累加分数
    int getScore(){return score;}               //获取分数, 渲染字体用
    void letItGo();                             //消除且计分
    bool add(Tetris* block);                    //方块堆叠

private:
    int score;

    bool judgeFull(int row);                    //判断是否满行, 是返回true, 否返回false
    void cleanPerRows(int row);                 //清除行
};

#endif
