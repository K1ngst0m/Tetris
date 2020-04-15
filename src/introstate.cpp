#include"introstate.h"
#include"menustate.h"
#include"reuse.h"

IntroState IntroState::m_introstate;

void IntroState::init(GameEngine* game){
    timi_engine  = irrklang::createIrrKlangDevice();
    logoa[0]     = loadTexture("resource/img/animations/logo1.jpg", game->renderer);
    logoa[1]     = loadTexture("resource/img/animations/logo2.jpg", game->renderer);
    logoa[2]     = loadTexture("resource/img/animations/logo3.jpg", game->renderer);
    logoa[3]     = loadTexture("resource/img/animations/logo4.jpg", game->renderer);
    logoa[4]     = loadTexture("resource/img/animations/logo5.jpg", game->renderer);
    logoa[5]     = loadTexture("resource/img/animations/logo6.jpg", game->renderer);
    logoa[6]     = loadTexture("resource/img/animations/logo7.jpg", game->renderer);
    logoa[7]     = loadTexture("resource/img/animations/logo8.jpg", game->renderer);
    logoa[8]     = loadTexture("resource/img/animations/logo9.jpg", game->renderer);
    logoa[9]     = loadTexture("resource/img/animations/logo10.jpg", game->renderer);
    logoa[10]    = loadTexture("resource/img/animations/logo11.jpg", game->renderer);
    logoa[11]    = loadTexture("resource/img/animations/logo12.jpg", game->renderer);
    logoa[12]    = loadTexture("resource/img/animations/logo13.jpg", game->renderer);
    logoa[13]    = loadTexture("resource/img/animations/logo14.jpg", game->renderer);
    logoa[14]    = loadTexture("resource/img/animations/logo15.jpg", game->renderer);
    logoa[15]    = loadTexture("resource/img/animations/logo16.jpg", game->renderer);
    logoa[16]    = loadTexture("resource/img/animations/logo17.jpg", game->renderer);
    logoa[17]    = loadTexture("resource/img/animations/logo18.jpg", game->renderer);
    logoa[18]    = loadTexture("resource/img/animations/logo19.jpg", game->renderer);
    logoa[19]    = loadTexture("resource/img/animations/logo20.jpg", game->renderer);
    logoa[20]    = loadTexture("resource/img/animations/logo21.jpg", game->renderer);
    exit = false;
}

void IntroState::clean_up(GameEngine* game){
    timi_engine->drop();
    IMG_Quit(); }

void IntroState::input(GameEngine* game){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT)
            exit = true;

        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
                exit = true; break;
            case SDLK_RETURN: game->push_state(MenuState::Instance());
            default: break;
            } } } }

void IntroState::update(GameEngine* game){
    if(exit) game->quit();
}

void IntroState::render(GameEngine* game){
    //清屏
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 1);
    for(int i = 0; i < 21; i++)
    {
        if(i == 1) timi_engine->play2D("resource/sounds/timi.ogg");
        if(i == 11) SDL_Delay(1900);

        SDL_RenderClear(game->renderer);

        render_logo(game, i);

        SDL_RenderPresent(game->renderer);
        SDL_Delay(135);
    }
    game->push_state(MenuState::Instance());
}

void IntroState::render_logo(GameEngine* game, int i){
    int logo_width, logo_height;
    SDL_QueryTexture(logoa[i], nullptr, nullptr, &logo_width, &logo_height);
    int x = game->width / 2 - logo_width / 2;
    int y = game->height / 2 - logo_height / 2;
    renderTexture(logoa[i], game->renderer, x, y);

}
