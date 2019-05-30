//初始界面, 显示logo后进入菜单界面
#ifndef SRC_INTORSTATE_H
#define SRC_INTORSTATE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<irrKlang.h>

#include"gamestate.h"

class IntroState: public GameState{
public:
    void init(GameEngine* game);                            //初始化初始界面
    void clean_up(GameEngine* game);                        //清理内存

    void pause(){}                                          //暂停(未使用)
    void resume(){}                                         //继续(未使用)
    void reset(){}                                          //重置游戏(未使用)

    void input(GameEngine* game);                           //窗口事件, 按键映射
    void update(GameEngine* game);                          //事件更新
    void render(GameEngine* game);                          //渲染图片, 显示画面

    static IntroState* Instance(){ return &m_introstate; }  //切换界面用

    void render_logo(GameEngine* game, int i);              //渲染logo

protected:
    IntroState(){}

private:
    static IntroState m_introstate;
    irrklang::ISoundEngine* timi_engine;

    bool exit;

    //LOGO
    SDL_Texture* logoa[21];                                 //存放一组图片,用来渲染logo动画
};
#endif
