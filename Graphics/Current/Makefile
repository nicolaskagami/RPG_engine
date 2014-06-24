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


all: Graphics

Graphics: clean main.o Graphics.o 
	g++ -o Graphics main.o Graphics.o $(LDFLAGS) 
main.o:
	g++ -c main.cpp -lSDL2
Graphics.o:
	g++ -c Graphics.cpp -lSDL2
clean:
	rm -rf *.o
