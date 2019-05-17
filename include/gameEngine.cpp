
#include"gameEngine.h"

GameEngine::GameEngine(){
    SDL_Init(SDL_INIT_EVERYTHING); //SDL启动
    //窗口长宽
    width = 500;
    height = 640;

    window = SDL_CreateWindow("Tetris for DMT",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN);//创建窗口
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                                //创建渲染器
    exit = false;
}
