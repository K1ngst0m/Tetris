#ifndef SRC_INTORSTATE_H
#define SRC_INTORSTATE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"gamestate.h"

class IntroState: public GameState{
public:
    void init(GameEngine* game);
    void clean_up(GameEngine* game);

    void pause();
    void resume();
    void reset();

    void input(GameEngine* game);
    void update(GameEngine* game);
    void render(GameEngine* game);

    static IntroState* Instance(){ return &m_introstate; }

    void render_logo(GameEngine* game, int i);

protected:
    IntroState(){}

private:
    static IntroState m_introstate;

    bool exit;

    //LOGO
    SDL_Texture* logoa[21];
    //SDL_Texture* logo;
    //int alpha;
    //enum Status {FADE_IN, REMAIN, FADE_OUT};
    //Status logo_status;
};
#endif
