#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include"reuse.h"
#include"playState.h"
#include"board.h"
#include"tetris.h"


class Tetris;
class Board;

PlayState PlayState::m_playstate;

void PlayState::init(GameEngine* game){

    board       = new Board();
    tetris       = new Tetris(rand()%7);
    next_tetris  = new Tetris(rand()%7);

    //砖块材质加载
    block_texture = loadTexture("", game->renderer);
}



