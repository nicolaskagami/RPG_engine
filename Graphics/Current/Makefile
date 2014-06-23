SDL_LIB = -lSDL2main -lSDL2
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
all: Graphics
Graphics: clean main.o Graphics.o 
	g++ -o Graphics main.o Graphics.o $(LDFLAGS) 
main.o:
	g++ -c main.cpp -lSDL2
GameClient.o:
	g++ -c Graphics.cpp -lSDL2
clean:
	rm -rf *.o
