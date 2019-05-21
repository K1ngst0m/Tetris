
#include<SDL2/SDL.h>
#include<vector>

class GameState;

class GameEngine{
public:
    GameEngine(); //SDL初始化
    void execute();
    void input();
    void update();
    void render();

    //窗口长宽
    int width;
    int height;

    //窗口和渲染器
    SDL_Window * window;
    SDL_Renderer * renderer;

private:

    bool exit;

};
