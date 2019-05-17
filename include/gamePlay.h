
class Board;

class Tetris{
public:
    //状态: 未使用, 待命, 下落中, 着陆
    enum Status {INACTIVE, WAITING, FALLING, LANDED};
    //移动状态: 未移动(左右), 左移, 右移
    enum Movement {NONE = 0, LEFT = -1, RIGHT = 1};
    static const int SIZE = 4; //方块边界

    //共有七个方块型(Z,J,O,T,S,I,L),每个型有四个方块, 分别存放四个方块的相对坐标
    static const int block_table[7][4][2];

    //改变坐标
    void setPoint(int xx, int yy){x = xx; y = yy;}
    void setX(int xx){x = xx;}
    void setY(int yy){y = yy;}
    //获取坐标
    int getX(int i){return x + relatLocate[i][0];}
    int getY(int i){return x + relatLocate[i][1];}

    Tetris(int n_type);
    //方块操作
    void rotateRight(); //右转
    void rotateLeft();  //左转
    void speedUp();     //加速
    void fallDown();    //直接下落


    Status status;
    Movement movement;
    int x, y; //方块型相对位置中(0,0)的全局坐标
    int (*relatLocate)[2]; //相对坐标
    int type;
};
