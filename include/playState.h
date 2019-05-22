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

    void releaseBlocks(); //下落一个新砖块
    void drawBlock(GameEngine* game, int x, int y, int k, SDL_Rect clips[]); //抽取方块

    Board* board;
    Tetris* tetris;
    Tetris* next_tetris;

    //Texture
    SDL_Texture* block_texture;

    //Fonts
    SDL_Color   white;
    TTF_Font*   font_pause;     //暂停时显示
    TTF_Font*   font_tetris;    //
    TTF_Font*   font_score_text;//
    TTF_Font*   font_score;     //

        //游戏结束显示
    TTF_Font*   font_new_game;
    TTF_Font*   font_quit;
    TTF_Font*   font_game_over;

    //Fonts-->texture
    SDL_Texture* font_image_pause;
    SDL_Texture* font_image_tetris;
    SDL_Texture* font_image_score_text;
    SDL_Texture* font_image_score;
    SDL_Texture* font_image_new_game;
    SDL_Texture* font_image_quit;
    SDL_Texture* font_image_game_over;

    bool newgamedown;
    bool newgameup;

    bool quitdown;
    bool quitup;

    int newgamex1;

    bool paused;
    bool game_over;
    bool exit;

};
