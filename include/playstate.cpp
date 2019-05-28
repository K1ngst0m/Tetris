#include"playstate.h"


#include"game_engine.h"
#include"tetromino.h"
#include"board.h"
#include"utilities.h"

PlayState PlayState::m_playstate;


void PlayState::init(GameEngine* game){

    board       = new Board();
    tetris       = new Tetris(rand()%7);
    next_tetris  = new Tetris(rand()%7);

    //砖块材质加载
    block_texture = loadTexture("resource/img/block.bmp", game->renderer);

    //字体载入
    TTF_Init();
    white = {255, 255, 255};
    font_tetris     = TTF_OpenFont("resource/fonts/MonsterFriendFore.otf", 16);
    font_score_text = TTF_OpenFont("resource/fonts/DTM-Mono.otf", 20);
    font_score      = TTF_OpenFont("resource/fonts/DTM-Sans.otf", 20);

    font_new_game   = TTF_OpenFont("resource/fonts/DTM-Mono.otf", 20);
    font_pause      = TTF_OpenFont("resource/fonts/DTM-Sans.otf", 16);
    font_game_over  = TTF_OpenFont("resource/fonts/DTM-Mono.otf", 20);
    font_quit       = TTF_OpenFont("resource/fonts/DTM-Mono.otf", 20);

    font_image_new_game     = renderText("NEW GAME" , white, font_new_game  , game->renderer);
    font_image_pause        = renderText("PAUSE"    , white, font_pause     , game->renderer);
    font_image_quit         = renderText("QUIT"     , white, font_quit      , game->renderer);
    font_image_game_over    = renderText("GAME OVER", white, font_game_over , game->renderer);
    font_image_tetris       = renderText("TETRIS"   , white, font_tetris    , game->renderer);
    font_image_score_text   = renderText("SCORE: "  , white, font_score_text, game->renderer);
    font_image_score        = renderText(std::to_string(board->getScore())  , white, font_score, game->renderer);

    acceleration    = 0.005f;
    this_time       = 0;
    last_time       = 0;
    time_till_drop  = 0.3f;
    time_counter    = 0.0f;

    newgamedown     = false;
    newgameup       = false;
    quitdown        = false;
    quitup          = false;

    newgamex1       = GAME_OFFSET+board->WINDOW_WIDTH+board->WTH_PER_BLOCK;
    newgamex2       = GAME_OFFSET+board->WINDOW_WIDTH+8*board->WTH_PER_BLOCK;
    newgamey1       = board->WINDOW_HEIGHT-4*board->HEI_PER_BLOCK;
    newgamey2       = board->WINDOW_HEIGHT-6*board->HEI_PER_BLOCK;

    //游戏状态
    paused          = false;
    game_over       = false;
    exit            = false;

    tetris->setPoint(static_cast<int>(board->COLS/2), 0);

    next_tetris->setPoint(board->COLS+5, static_cast<int>(0.3*board->ROWS));

}


void PlayState::clean_up(GameEngine* game){

    TTF_CloseFont(font_tetris);
    TTF_CloseFont(font_score);
    TTF_CloseFont(font_score_text);
    TTF_CloseFont(font_new_game);
    TTF_CloseFont(font_pause);
    TTF_CloseFont(font_game_over);
    TTF_CloseFont(font_quit);

    SDL_DestroyTexture(font_image_pause);
    SDL_DestroyTexture(font_image_tetris);
    SDL_DestroyTexture(font_image_score_text);
    SDL_DestroyTexture(font_image_score);
    SDL_DestroyTexture(font_image_new_game);
    SDL_DestroyTexture(font_image_quit);
    SDL_DestroyTexture(font_image_game_over);

    IMG_Quit();

    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);
    SDL_Quit();
}

void PlayState::pause(){
    paused = true;
}

void PlayState::resume(){
    paused = false;
}

void PlayState::reset(){
    for(int i = 0; i < board->ROWS; i++)
        for(int j = 0; j < board->COLS; j++)
            board->color[i][j] = -1;

    //删除旧有的对象
    delete [] board;
    delete [] tetris;
    delete [] next_tetris;

    //重新创建对象
    board = new Board();
    tetris = new Tetris(rand()%7);
    next_tetris = new Tetris(rand()%7);

    tetris->setPoint(static_cast<int>(board->COLS/2), 0);
    next_tetris->setPoint(board->COLS+5, static_cast<int>(0.3*board->ROWS));

    game_over            = false;
    newgameup            = false;
    newgamedown          = false;

    paused = false;

}
void PlayState::input(GameEngine* game){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        //退出事件
        if(event.type == SDL_QUIT){
            exit = true;
        }

        //键盘按下事件
        if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_p){
                if(paused)      resume();
                else            pause(); }

            //方块操作
        if(!paused && !tetris->fall){
            switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
                exit = true; break;
            // a 方向键左: 左移动
            case SDLK_a: case SDLK_LEFT:
                tetris->movement = tetris->LEFT;
                tetris->shift = true; break;
            // d 方向键右: 右移动
            case SDLK_d: case SDLK_RIGHT:
                tetris->movement = tetris->RIGHT;
                tetris->shift = true; break;
            // w 方向键上: 方块旋转(O型方块除外)
            case SDLK_w: case SDLK_UP:
                if (tetris->type != 2) //O
                    tetris->rotate = true;
                break;
            // s 方向键下: 方块加速下落
            case SDLK_s: case SDLK_DOWN:
                tetris->speedup = true; break;
            // 空格键: 方块直接落地
            case SDLK_SPACE:
                tetris->fall = true;
            default: break;
            } }
        }


        //键盘松开事件
        if(event.type == SDL_KEYUP){
            switch(event.key.keysym.sym){
            case SDLK_s: case SDLK_DOWN:
                tetris->speedup = false; break;
            default: break;
            }
        }

        //鼠标移动事件
        if(event.type == SDL_MOUSEMOTION){
            //方块池外
            if(event.motion.x > board->WINDOW_WIDTH + GAME_OFFSET)
                SDL_ShowCursor(1);      //显示光标(方块池外)
            //方块池内
            else
                SDL_ShowCursor(0);      //隐藏光标(方块池内)
        }

        //鼠标点击事件
        if(event.type == SDL_MOUSEBUTTONDOWN){
            switch(event.button.button){
            case SDL_BUTTON_LEFT: {
            int x = event.button.x;
            int y = event.button.y;
            if (x > newgamex1 && x < newgamex2){
                if(y > newgamey2 && y < newgamey1)
                    //光标置于"NEW GAME" 位置
                    { newgamedown = true; }
                else if (y > newgamey2 + 4*board->HEI_PER_BLOCK &&
                         y < newgamey1 + 4*board->HEI_PER_BLOCK){
                    //光标置于"QUIT"位置
                    quitdown = true; } } break; }
            default: break; } }

        //鼠标松开事件
        if(event.type == SDL_MOUSEBUTTONDOWN){ switch(event.button.button){
            case SDL_BUTTON_LEFT: {
            int x = event.button.x;
            int y = event.button.y;
            if (x > newgamex1 && x < newgamex2){
                if(y > newgamey2 && y < newgamey1)
                    //光标置于"NEW GAME" 位置
                    newgameup = true;
                else if (y > newgamey2 + 4*board->HEI_PER_BLOCK &&
                         y < newgamey1 + 4*board->HEI_PER_BLOCK){
                    //光标置于"QUIT"位置
                    quitup = true; } } break; }
            default: break; } }
}}

void PlayState::releaseBlocks(){
    Tetris* new_tetris = new Tetris(rand()%7);
    new_tetris->setPoint(next_tetris->x, next_tetris->y);

    delete[] tetris;
    tetris = next_tetris;
    tetris->setPoint(static_cast<int>(board->COLS/2), 0);

    next_tetris = new_tetris;

    tetris->drop();
}

void PlayState::update(GameEngine* game){
    //按下NEW GAME
    if(newgameup && newgamedown)
        reset();

    // 按下QUIT
    if((quitup && quitdown) || exit)
        game->quit();

    if(game_over || paused)
        return;

    // 方块落地时处理
    if (tetris->has_landed()){
        tetris->fall = false;
        if(!board->add(tetris)){
            game_over = true;
            return; }
        releaseBlocks();
    }else if(tetris->fall){
        tetris->y++;//加速
    }else{
        if(tetris->rotate)
            tetris->rotateLeft();
        tetris->add_to_x(tetris->movement);

        if(tetris->speedup){
            time_till_drop = 0.02f;
        }else{
            time_till_drop = 0.3f - board->getScore()*acceleration;
        }

        time_counter += frame_rate(game, &last_time, &this_time);

        if(time_counter >= time_till_drop){
            tetris->y++;
            time_counter = 0.0f;
        }
    }

    for(int i = 0; i < tetris->SIZE; i++){
        int x = tetris->getX(i);
        int y = tetris->getY(i);

        if(x < 0 || x >= board->COLS){
            if(tetris->rotate)
                tetris->rotateRight();

            if(tetris->shift)
                tetris->x -= tetris->movement;
            break;

        }else if(y >= board->ROWS){
            tetris->lands();

            tetris->setY(i, board->ROWS-1);
        }else if(y >= 0){
            if(board->color[y][x] != -1){
                if(tetris->rotate || tetris->shift){
                    if(tetris->rotate){
                        tetris->rotateRight();
                    }
                    if(tetris->shift){
                        tetris->x -= tetris->movement;
                    }
                    break;
                }else{
                    tetris->y--;
                    tetris->lands();
                }
            }
        }
    }
    board->letItGo();
    tetris->rotate = false;
    tetris->shift = false;
    tetris->movement = tetris->NONE;
}

void PlayState::render(GameEngine* game){
    SDL_SetRenderDrawColor(game->renderer, 0, 1, 0, 1);
    SDL_RenderClear(game->renderer);

    //渲染 "TETRIS" 文字
    int x = (next_tetris->x-3) * board->WTH_PER_BLOCK;
    int y = GAME_OFFSET;

    renderTexture(font_image_tetris, game->renderer, x, y);
    //渲染 "PAUSE" 文字
    if(paused)
        renderTexture(font_image_pause, game->renderer, x, y+40);
    //渲染"SCORE"文字
    renderTexture(font_image_score_text, game->renderer, x, y + board->WTH_PER_BLOCK);
    //渲染分数
    if(board->render_score){
        font_image_score = renderText(std::to_string(board->getScore()),
                                      white, font_score, game->renderer);
        board->render_score = false;
    }
    renderTexture(font_image_score,
                  game->renderer, x + 60, y + board->WTH_PER_BLOCK);

    int  block_x, block_y;

    int iW, iH;
    SDL_QueryTexture(block_texture, nullptr, nullptr, &iW, &iH);

    SDL_Rect clips[7];
    for(int i = 0; i < 7; i++){
        clips[i].x = 0;
        clips[i].y = i*24;
        clips[i].w = 20;
        clips[i].h = 20;
    }

    for(int i = 0; i < tetris->SIZE; i++){
        block_x = tetris->getX(i)*board->WTH_PER_BLOCK + GAME_OFFSET;
        block_y = tetris->getY(i)*board->WTH_PER_BLOCK + GAME_OFFSET;

        drawBlock(game, block_x, block_y, tetris->type, clips);
    }

    int shadow_y[4];
    tetris->getShadow(board, shadow_y);
    for(int i = 0; i < tetris->SIZE; i++){
        if(shadow_y[i] < 0)
            break;
        int x = tetris->getX(i)*board->WTH_PER_BLOCK + GAME_OFFSET;
        int y = shadow_y[i]*board->WTH_PER_BLOCK + GAME_OFFSET;

        SDL_SetRenderDrawColor(game->renderer, 180, 180, 180, 255);
        SDL_Rect shadow_block = {x, y, board->WTH_PER_BLOCK, board->HEI_PER_BLOCK};
        SDL_RenderFillRect(game->renderer, &shadow_block);
    }

    if(!game_over){
        for(int i = 0; i < next_tetris->SIZE; i++){
            block_x = next_tetris->getX(i)*board->WTH_PER_BLOCK;
            block_y = next_tetris->getY(i)*board->HEI_PER_BLOCK;

            drawBlock(game, block_x, block_y, next_tetris->type, clips);
        }
    }
    //方块池待命方块
    for(int i = 0; i < board->ROWS; i++)
        for(int j = 0; j < board->COLS; j++)
            if(board->color[i][j] != -1) {
                block_x = j*board->WTH_PER_BLOCK + GAME_OFFSET;
                block_y = i*board->HEI_PER_BLOCK + GAME_OFFSET;

                drawBlock(game, block_x, block_y, board->color[i][j], clips);
            }

    SDL_SetRenderDrawColor(game->renderer, 180, 180, 180, 255);

    //方块池右边缘
    SDL_RenderDrawLine(game->renderer,
                       GAME_OFFSET, GAME_OFFSET,
                       GAME_OFFSET, GAME_OFFSET + board->WINDOW_HEIGHT);
    //方块池左边缘
    SDL_RenderDrawLine(game->renderer,
                       GAME_OFFSET+board->WINDOW_WIDTH, GAME_OFFSET,
                       GAME_OFFSET+board->WINDOW_HEIGHT, GAME_OFFSET+board->WINDOW_HEIGHT);

    //方块池顶边缘
    SDL_RenderDrawLine(game->renderer,
                       GAME_OFFSET, GAME_OFFSET,
                       GAME_OFFSET+board->WINDOW_WIDTH, GAME_OFFSET);

    //方块池底边缘
    SDL_RenderDrawLine(game->renderer,
                       GAME_OFFSET, GAME_OFFSET+board->WINDOW_HEIGHT,
                       GAME_OFFSET+board->WINDOW_WIDTH, GAME_OFFSET+board->WINDOW_HEIGHT);

    if (game_over)
        renderTexture(font_image_game_over,
                      game->renderer, newgamex1,
                      game->height-newgamey1+4*board->WTH_PER_BLOCK);

    //"NEW GAME" 按钮框
    int blue[4] = {0, 0, 255, 255};
    createButton(game, newgamex1, newgamey2,
                 7*board->WINDOW_WIDTH, 2*board->WINDOW_HEIGHT, blue);

    //渲染"NEW GAME"文字
    renderTexture(font_image_new_game,
                  game->renderer, newgamex1+10, newgamey2+10);

    //"QUIT" 按钮框
    int red[4] = {255, 0, 0, 255};
    createButton(game, newgamex1,
                 newgamey2 + 4*board->HEI_PER_BLOCK, 7*board->WTH_PER_BLOCK,
                 2*board->HEI_PER_BLOCK, red);

    //渲染"QUIT"文字
    renderTexture(font_image_quit,
                  game->renderer, newgamex1+10, newgamey2+4*board->HEI_PER_BLOCK+10);

    //显示内容
    SDL_RenderPresent(game->renderer);
}

void PlayState::createButton(GameEngine* game,
                             int x, int y,
                             int width, int height, int color[]){
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(game->renderer,
                             color[0], color[1], color[2], color[3]);
    SDL_RenderFillRect(game->renderer, &rect);
}


void PlayState::drawBlock(GameEngine* game,
                          int x, int y, int k, SDL_Rect clips[]){
    renderTexture(block_texture, game->renderer, x, y, &clips[k]);
}


float PlayState::frame_rate(GameEngine* game, int* last_time, int* this_time){
    *last_time = *this_time;

    *this_time = SDL_GetTicks();

    return ((*this_time - *last_time) / 1000.0f);
}
