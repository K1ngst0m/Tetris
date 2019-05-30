#ifndef SRC_GAME_ENGINE_H_
#define SRC_GAME_ENGINE_H_

#include<SDL2/SDL.h>
#include<vector>

class GameState;

class GameEngine{
public:
    GameEngine();                       //SDL初始化

    void clean_up();                    //清理内存

    void change_state(GameState* state);//更换界面
    void push_state(GameState* state);  //
    void pop_state();                   //

    void execute();                     //启动引擎
    void input();                       //输入
    void update();
    void render();                      //渲染界面

    bool runnning(){return !exit;}      //
    void quit(){exit = true;}           //退出游戏(程序)

    //窗口长宽
    int width;
    int height;

    //窗口和渲染器
    SDL_Window * window;                //窗口
    SDL_Renderer * renderer;            //渲染器

private:

    std::vector<GameState*> states;     //栈

    bool exit;

};
#endif
