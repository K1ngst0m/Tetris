#ifndef _GAMEENGINE_H
#define _GAMEENGINE_H
#include<SDL2/SDL.h>
#include<vector>

class GameState;

class GameEngine{
public:
    GameEngine(); //SDL初始化

    void clean_up();

    void change_state(GameState* state);
    void push_state(GameState* state);
    void pop_state();

    void execute();
    void input();
    void update();
    void render();

    void quit(){exit = true;}

    //窗口长宽
    int width;
    int height;

    //窗口和渲染器
    SDL_Window * window;
    SDL_Renderer * renderer;

private:

    std::vector<GameState*> states;
    bool exit;

};
#endif
