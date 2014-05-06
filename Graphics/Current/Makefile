Graphics: clean main.o Graphics.o 
	g++ -o Graphics main.o Graphics.o -lSDL2
main.o:
	g++ -c main.cpp -lSDL2
GameClient.o:
	g++ -c Graphics.cpp -lSDL2
clean:
	rm -rf *.o
