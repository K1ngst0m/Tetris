#ifndef _PLAYSTATE_H
#define _PLAYSTATE_H

#include"irrKlang.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include<random>

#include"gameState.h"

class Tetris;
class Board;

class PlayState : public GameState{
public:
    static const int NOLORS = 7;

    static const int GAME_OFFSET = 20;

    void init(GameEngine* game);        //系统初始化
    void reset();                       //重置游戏
    void cleanUp(GameEngine *game);     //清理内存


    void input(GameEngine* game);       //设置键盘, 鼠标, 窗口事件
    void update(GameEngine* game);      //事件更新
    void render(GameEngine* game);      //渲染结果

    static PlayState* Instance(){ return &m_playstate; }

protected:
    PlayState(){}
private:
    static PlayState m_playstate;

    void releaseBlocks(); //下落一个新砖块
    void drawBlock(GameEngine* game, int x, int y, int k, SDL_Rect clips[]); //抽取方块
    float frame_rate(GameEngine* game, int *last_time, int *this_time);
    void createButton(GameEngine* game,
                       int x, int y,
                       int width, int height, int color[]);

    Board* board;
    Tetris* tetris;
    Tetris* next_tetris;

    //Texture
    SDL_Texture* block_texture;

    //Fonts
    SDL_Color   white;
    TTF_Font*   font_pause;     //暂停时显示
    TTF_Font*   font_tetris;    //
    TTF_Font*   font_score_text;//
    TTF_Font*   font_score;     //

        //游戏结束显示
    TTF_Font*   font_new_game;
    TTF_Font*   font_quit;
    TTF_Font*   font_game_over;

    //Fonts-->texture
    SDL_Texture* font_image_pause;
    SDL_Texture* font_image_tetris;
    SDL_Texture* font_image_score_text;
    SDL_Texture* font_image_score;
    SDL_Texture* font_image_new_game;
    SDL_Texture* font_image_quit;
    SDL_Texture* font_image_game_over;

    //帧相关
    float acceleration;
    int this_time;
    int last_time;
    float time_till_drop;
    float time_counter;

    //键盘事件状态
    bool newgamedown;   //按下开始键
    bool newgameup;     //松开开始键
    bool quitdown;      //按下退出键
    bool quitup;        //松开退出键

    //选项坐标
    int newgamex1;
    int newgamex2;
    int newgamey1;
    int newgamey2;

    bool paused;
    bool game_over;     //当游戏结束时返回true
    bool exit;          //当退出游戏是返回quit
};

#endif
