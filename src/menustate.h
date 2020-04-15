//菜单界面, 选择进入游戏或者退出
#ifndef SRC_MENUSTATE_H_
#define SRC_MENUSTATE_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<irrKlang.h>

#include"gamestate.h"

class MenuState: public GameState{
public:
    void init(GameEngine* game);                        //初始化, 显示图片和字体, 播放音乐
    void clean_up(GameEngine* game);                    //清理内存

    void pause(){}                                      //暂停(未使用)
    void resume(){}                                     //继续(未使用)
    void reset(){}                                      //重置(未使用)

    void input(GameEngine* game);                       //菜单选择操作等
    void update(GameEngine* game);                      //对操作进行更新
    void render(GameEngine* game);                      //渲染背景图片, 标题, 选项字体, 显示画面

    void select_up();                                   //向上选择
    void select_down();                                 //向下选择

    static MenuState* Instance() {return &m_menustate;} //界面选择用

protected:
    MenuState(){}

private:
    static MenuState m_menustate;

    //游玩与退出选项
    bool play;
    bool exit;

    //背景图片
    SDL_Texture*        background;

    //背景音乐
    irrklang::ISoundEngine* music_engine;
    irrklang::ISoundEngine* select_engine;

    //字体渲染
    SDL_Color           white;
    TTF_Font*           font_title;
    TTF_Font*           font_play;
    TTF_Font*           font_quit;
    SDL_Texture*        font_image_title;
    SDL_Texture*        font_image_play;
    SDL_Texture*        font_image_quit;

    //文字位置
    int title_width,    title_height;
    int play_width ,    play_height;
    int quit_width ,    quit_height;


    int currently_selected;

    int items;

};
#endif
