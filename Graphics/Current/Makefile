#Makefile Supports Both Windows (under mingw) and linux
SDL_LIB = -lSDL2main -lSDL2
SYS := $(shell gcc -dumpmachine)
ifneq (, $(findstring linux, $(SYS)))
	LDFLAGS = $(SDL_LIB)
else ifneq(, $(findstring mingw, $(SYS)))
	LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
else
	echo "Unrecognized Option"
endif


all: Game

Game: main.o Game.o TextureManager.o
	g++ -o game main.o TextureManager.o Game.o $(LDFLAGS) 
main.o: main.cpp
	g++ -c main.cpp -lSDL2
Game.o: Game.cpp
	g++ -c Game.cpp -lSDL2
TextureManager.o: TextureManager.cpp
	g++ -c TextureManager.cpp -lSDL2

clean:
	rm -rf *.o
