
#include"include/game_engine.h"
#include"include/introstate.h"

int main(int argc, char* argv[]){
    GameEngine game;                            //初始化游戏
    game.change_state(IntroState::Instance());  //进入初始界面
    game.execute();                             //启动相关界面输入, 渲染, 更新事件功能, 并在退出时释放内存
}
