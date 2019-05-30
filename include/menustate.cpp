#include"menustate.h"
#include"playstate.h"
#include"reuse.h"

MenuState MenuState::m_menustate;

void MenuState::init(GameEngine* game){
    play = false;
    exit = false;

    TTF_Init();
    white = {255, 255, 255};

    background  = loadTexture("resource/img/menu.png", game->renderer);
    font_title  = TTF_OpenFont("resource/fonts/MonsterFriendFore.otf", 60);
    font_play   = TTF_OpenFont("resource/fonts/MonsterFriendFore.otf", 20);
    font_quit   = TTF_OpenFont("resource/fonts/MonsterFriendFore.otf", 20);

    font_image_title    = renderText("TETRIS", white, font_title, game->renderer);
    font_image_play     = renderText("PLAY"  , white, font_play , game->renderer);
    font_image_quit     = renderText("QUIT"  , white, font_quit , game->renderer);

    //文字位置
    SDL_QueryTexture(font_image_title, nullptr, nullptr , &title_width, &title_height);
    SDL_QueryTexture(font_image_play , nullptr, nullptr , &play_width , &play_height);
    SDL_QueryTexture(font_image_quit , nullptr, nullptr , &quit_width , &quit_height);

    currently_selected = 0;
    items = 2;
}

void MenuState::clean_up(GameEngine* game){
    //字体清理
    TTF_CloseFont(font_title);
    TTF_CloseFont(font_play);
    TTF_CloseFont(font_quit);

    SDL_DestroyTexture(font_image_title);
    SDL_DestroyTexture(font_image_play);
    SDL_DestroyTexture(font_image_quit);

    IMG_Quit();
}

void MenuState::pause(){}
void MenuState::resume(){}
void MenuState::reset(){}

void MenuState::input(GameEngine* game){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            exit = true;
        }

        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
                exit = true;
                break;
            case SDLK_UP:
                select_up(); break;
            case SDLK_DOWN:
                select_down(); break;
            case SDLK_RETURN:
                if(currently_selected == 0)
                    play = true;
                else if (currently_selected == 1)
                    exit = true;
                break;
            default:
                break;
            }
        }
    }
}

void MenuState::update(GameEngine* game){
    if(play){
        game->push_state(PlayState::Instance());
    }else if (exit){
        game->quit();
    }
}

void MenuState::render(GameEngine* game){
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 1);
    SDL_RenderClear(game->renderer);

    int height, width;
    int space = 30;

    renderTexture(background, game->renderer, 0, 0);
    SDL_QueryTexture(font_image_title, nullptr, nullptr, &width, &height);
    renderTexture(font_image_title, game->renderer,
                   (game->width- title_width) / 2,
                   (game->height - title_height) / 2 - space * 2);

    if(currently_selected == 0){
        TTF_SetFontStyle(font_play, TTF_STYLE_UNDERLINE);
        font_image_play = renderText("PLAY", white, font_play, game->renderer);
    }else if(currently_selected == 1){
        TTF_SetFontStyle(font_quit, TTF_STYLE_UNDERLINE);
        font_image_quit = renderText("QUIT", white, font_quit, game->renderer);
    }

    renderTexture(font_image_play, game->renderer,
                  (game->width - play_width) / 2, (game->height - play_height) / 2);
    renderTexture(font_image_quit, game->renderer,
                  (game->width - quit_width) / 2,(game->height - quit_height) / 2+space);

    if(currently_selected == 0){
        TTF_SetFontStyle(font_play, TTF_STYLE_NORMAL);
        font_image_play = renderText("PLAY", white, font_play, game->renderer);
    }else if(currently_selected == 1){
        TTF_SetFontStyle(font_quit, TTF_STYLE_NORMAL);
        font_image_quit = renderText("QUIT", white, font_quit, game->renderer);
    }

    SDL_RenderPresent(game->renderer);
}

void MenuState::select_up(){
    if(currently_selected > 0){
        currently_selected = (currently_selected - 1) % items;
    }
}

void MenuState::select_down(){
    if(currently_selected < items-1){
        currently_selected = (currently_selected + 1) % items;
    }
}
