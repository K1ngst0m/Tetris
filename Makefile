BINARY 			:= tetris
SRCS			:= $(wildcard include/*.cpp)
OBJS			:= $(SRCS:.cpp=.o)

DEBUG			:= -g

SDL_INCLUDE		:= `sdl2-config --cflags` -IirrKlang-64bit-1.5.0/include -I.
SDL_LIB			:= `sdl2-config --libs` -lSDL2_ttf -lSDL2_image ./irrKlang-64bit-1.5.0/bin/linux-gcc-64/libIrrKlang.so

CPPFLAGS		+= $(SDL_INCLUDE)
CXXFLAGS		+= $(DEBUG) -Wall -std=c++0x
LDFLAGS			+= $(SDL_LIB)

.PHONY: all clean

all: $(BINARY)

$(BINARY): $(OBJS)
	$(LINK.cpp) $(OBJS) -o $(BINARY) $(LDFLAGS)

clean:
	@- $(RM) $(BINARY)
	@- $(RM) $(OBJS)
