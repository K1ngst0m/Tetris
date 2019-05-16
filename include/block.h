#ifdef BLOCK_H
#define BLOCK_H

class Block{
public:
    char BLOCKS[20][5][5];
    int NEXT[20];
    void moveLR();
    //左右移动
    void speedup();
    //加速
    void change();
    //旋转
    bool detect(int);
};



#endif
