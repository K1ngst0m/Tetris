#ifndef _MENUSTATE_H
#define _MENUSTATE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#include"gameState.h"

class MenuState: public GameState{
public:
    void init(GameEngine* game);
    void cleanUp(GameEngine* game);

    void pause();
    void resume();
    void reset();

    void input(GameEngine* game);
    void update(GameEngine* game);
    void render(GameEngine* game);

    void select_up();
    void select_down();

    static MenuState* Instance() {return &m_menustate;}

protected:
    MenuState(){}

private:
    static MenuState m_menustate;

    bool play;
    bool exit;

    SDL_Color       white;
    TTF_Font*       font_title;
    TTF_Font*       font_play;
    TTF_Font*       font_quit;
    SDL_Texture*       font_image_title;
    SDL_Texture*       font_image_play;
    SDL_Texture*       font_image_quit;

    //文字位置
    int title_width, title_height;
    int play_width, play_height;
    int quit_width, quit_height;

    int currently_selected;

    int items;

};
#endif
