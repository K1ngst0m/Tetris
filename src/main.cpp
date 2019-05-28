
#include"game_engine.h"
#include"introstate.h"

int  main(int argc, char* argv[]){
    GameEngine game;
    game.change_state(IntroState::Instance());
    game.execute();
}
