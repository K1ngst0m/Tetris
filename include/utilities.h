#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<string>

//调用SDL_RenderCopy
void renderTexture(SDL_Texture* tex,
                  SDL_Renderer* ren,
                  SDL_Rect dst,
                  SDL_Rect* clip = nullptr);

//调用SDL_RenderCopy
void renderTexture(SDL_Texture* tex,
                  SDL_Renderer* ren,
                  int x, int y,
                  SDL_Rect* clip = nullptr);

//编写一个文本, 得到一个SDL_texture指针
SDL_Texture* renderText(const std::string &message,
                       SDL_Color color,
                       TTF_Font* font,
                       SDL_Renderer* renderer);

//加载图片, 得到一个SDL_texture指针
SDL_Texture* loadTexture(const std::string &file,
                         SDL_Renderer* ren);
#endif
