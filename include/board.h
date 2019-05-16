
//游戏窗口边界 Board类
class Board{ //方块池
public:
    static const int WINDOW_WIDTH = 300;//宽度
    static const int WINDOW_HEIGHT = 600;//高度

    static const int ROWS = 30; //行数
    static const int COLS = 15; //列数

    static const int HEI_PER_BLOCK = WINDOW_HEIGHT / COLS; //行高度
    static const int WTH_PER_BLOCK = WINDOW_WIDTH / ROWS;  //列高度

    int color[ROWS][COLS]; //二维数组表示方块坐标

    Board();    //方块池初始化

    void letItGo();

private:
    int score;
    bool judgeFull(int row); //判断是否满行, 是返回true, 否返回false
    void cleanPerRows(int row); //清除行
};
