#ifndef SRC_GAME_ENGINE_H_
#define SRC_GAME_ENGINE_H_

#include <vector>
#include <SDL2/SDL.h>
#include "IrrKlang/irrKlang.h"

class GameState;

class GameEngine{
public:
    GameEngine();                       //SDL初始化

    void clean_up();                    //退出程序时清理内存

    //栈操作
    void change_state(GameState* state);//更换界面
    void push_state(GameState* state);  //增加一个游戏界面
    void pop_state();                   //删除一个游戏界面

    void execute();                     //保持下列操作启动
    void input();                       //启动事件映射
    void update();                      //启动事件更新
    void render();                      //启动渲染界面

    bool running() const{return !exit;}
    void quit(){exit = true;}           //退出游戏(程序)

    //窗口长宽
    int width;
    int height;

    //窗口和渲染器
    SDL_Window * window;                //窗口
    SDL_Renderer * renderer;            //渲染器

private:

    std::vector<GameState*> states;     //栈结构,用来管理游戏界面运行, 切换, 清理内存

    bool exit;                          //ture退出程序

};
#endif
