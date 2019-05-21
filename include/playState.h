#include"irrKlang.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include"gameState.h"

class Tetris;
class Board;

class PlayState : public GameState{
public:
    static const int NOLORS = 7;

    static const int GAME_OFFSET = 20;

    void init(GameEngine* game);        //系统初始化
    void cleanUp(GameEngine *game);

    void pause();
    void resume();
    void reset();

    void input(GameEngine* game);
    void update(GameEngine* game);
    void render(GameEngine* game);


protected:
    PlayState(){}
private:
    static PlayState m_playstate;

    void release_tetris(); //下落一个新砖块

};
