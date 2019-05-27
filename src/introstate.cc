#include"introstate.h"
#include"menustate.h"
#include"reuse.h"

IntroState IntroState::m_introstate;

void IntroState::init(GameEngine* game){
    logo = loadTexture("../resource/img/logo.png", game->renderer);
    exit = false;
    alpha = 1;
    logo_status = FADE_IN;
}

void IntroState::cleanUp(GameEngine* game){
    IMG_Quit();
}

void IntroState::pause(){}

void IntroState::resume(){}

void IntroState::reset(){}

void IntroState::input(GameEngine* game){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT)
            exit = true;

        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
                exit = true;
                break;
            default:
                break;
            }
        }
    }
}

void IntroState::update(GameEngine* game){
    if(exit){
        game->quit();
    }

    if(alpha == 0){
        game->push_state(MenuState::Instance());
    }
}

void IntroState::render(GameEngine* game){
    //清屏
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 1);
    SDL_RenderClear(game->renderer);

    render_logo(game);

    //显示
    SDL_RenderPresent(game->renderer);
}

void IntroState::render_logo(GameEngine* game){
    if(logo_status == FADE_IN){
        alpha += 3;
        if(alpha >= 255){
            alpha = 255;
            logo_status = REMAIN;
        }
    }   else if(logo_status == REMAIN){
        SDL_Delay(2000);
        logo_status = FADE_OUT;
    }   else if(logo_status == FADE_OUT){
        alpha -= 3;
        if(alpha <= 0){
            alpha = 0;
            logo_status = FADE_IN;
        }
    }
    SDL_SetTextureAlphaMod(logo, alpha);

    int logo_width, logo_height;
    SDL_QueryTexture(logo, nullptr, nullptr, &logo_width, &logo_height);
    int x = game->width / 2 - logo_width / 2;
    int y = game->height / 2 - logo_height / 2;

    renderTexture(logo, game->renderer, x, y);
}
