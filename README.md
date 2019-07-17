# C++实训: 俄罗斯方块

## 游戏截图
![1](https://github.com/npchitman/tetris/blob/master/screenshot/1.png?raw=true)
![2](https://github.com/npchitman/tetris/blob/master/screenshot/2.png?raw=true)
![3](https://github.com/npchitman/tetris/blob/master/screenshot/3.png?raw=true)
![4](https://github.com/npchitman/tetris/blob/master/screenshot/4.png?raw=true)
![5](https://github.com/npchitman/tetris/blob/master/screenshot/5.png?raw=true)
![6](https://github.com/npchitman/tetris/blob/master/screenshot/6.png?raw=true)
## 安装方法
### Linux:
安装依赖项 libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
```bash
$ git clone https://github.com/npchitman/tetris
$ cd tetris
$ make
```
### Windows:


## 开发环境及依赖
* linux
* 第三方库:SDL2
    * SDL_ttf
    * SDL_image
* 声音引擎:irrklang

## 开发工具
* 文本编辑器: vim
* 编译器: g++
* 图片处理: sai2, photoshop
* 声音处理: flstudio

## 开发内容
* 游戏引擎
* UI设计
    * 开始界面
    * 游玩界面
    * 暂停界面(暂定)
    * 游戏结束界面(暂定)
* 方块设计
    * 7种方块(Z, J, O, T, S, I, L)
* 方块操作
    * 左右:方块移动
    * 上:旋转
    * 下:加速
* 游戏机制
    * 方块消除判定
    * 得分判定
    * 游戏结束判定
* 声音
    * 音效
    * 背景音乐
