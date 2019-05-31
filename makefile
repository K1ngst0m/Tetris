CXX        		:= clang++
SRCS			:= $(wildcard include/*.cpp)
OBJS			:= $(SRCS:.cpp=.o)


SDL_INCLUDE		:= `sdl2-config --cflags` -IirrKlang-64bit-1.5.0/include -I.
SDL_LIB			:= `sdl2-config --libs` -lSDL2_ttf -lSDL2_image ./irrKlang-64bit-1.5.0/bin/linux-gcc-64/libIrrKlang.so

CPPFLAGS		+= $(SDL_INCLUDE)
CXXFLAGS		+= -Wall -g -std=c++14
LDFLAGS			+= $(SDL_LIB)

tetris: $(OBJS)
	clang++ $(OBJS) -o tetris $(LDFLAGS)

clean:
	 $(RM) tetris
	 $(RM) $(OBJS)