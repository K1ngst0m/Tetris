#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include "game_engine.h"

class GameState{
public:
    //游戏界面功能
    virtual void init(GameEngine *game) = 0;        //启动游戏
    virtual void cleanUp(GameEngine *game) = 0;     //清理游戏内存

    virtual void pause() = 0;                       //暂停
    virtual void resume() = 0;                      //继续

    virtual void input(GameEngine *game) = 0;       //输入
    virtual void update(GameEngine *game) = 0;      //更新
    virtual void render(GameEngine *game) = 0;      //渲染

    void changestate(GameEngine* game, GameState* state){
        game->change_state(state);
    }

protected:
    GameState(){}
};
#endif
