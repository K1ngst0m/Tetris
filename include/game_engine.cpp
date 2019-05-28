
#include"game_engine.h"
#include"gamestate.h"

GameEngine::GameEngine(){
    SDL_Init(SDL_INIT_EVERYTHING);
    //if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        //std::cout << SDL_GetError() << std::endl;
    //} //SDL启动

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
    //if (window == nullptr){ std::cout << SDL_GetError() << std::endl; }


    //创建渲染器
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //if (renderer == nullptr){ std::cout << SDL_GetError() << std::endl; }

    exit = false;
}

void GameEngine::execute(){
    while(!exit){
        input();
        update();
        render();
    }
    clean_up();
}

void GameEngine::clean_up(){
    while(!states.empty()){
        states.back()->clean_up(this);
        states.pop_back();
    }

    SDL_Quit();
}

void GameEngine::change_state(GameState* state){
    if(!states.empty()){
        states.back()->clean_up(this);
        states.pop_back();
    }

    states.push_back(state);
    states.back()->init(this);
}

void GameEngine::push_state(GameState* state){

    if(!states.empty())
        states.back()->pause();

    states.push_back(state);
    states.back()->init(this);
}

void GameEngine::pop_state(){
    if(!states.empty()){
        states.back()->clean_up(this);
        states.pop_back();
    }
    if(!states.empty())
        states.back()->resume();
}

void GameEngine::input(){
    states.back()->input(this);
}

void GameEngine::update(){
    states.back()->update(this);
}

void GameEngine::render(){
    states.back()->render(this);
}
