
#include"gameEngine.h"
#include"iostream"
#include<cstdlib>

GameEngine::GameEngine(){
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << SDL_GetError() << std::endl;
    } //SDL启动

    //窗口长宽
    width = 500;
    height = 640;

    //创建窗口
    window = SDL_CreateWindow("Tetris for DMT",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr){ std::cout << SDL_GetError() << std::endl; }


    //创建渲染器
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){ std::cout << SDL_GetError() << std::endl; }

    exit = false;
}
