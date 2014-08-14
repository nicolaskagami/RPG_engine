//Main tester for Graphics
//Author: Nicolas Silveira Kagami

#include <stdio.h>
#include "SDL2/SDL.h"
#include "Game.h"
#include "TextureManager.h"

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 640 
#define WINDOW_TITLE "Main Window (so far...)"


int main(int argc, char* args[])
{
    
    TheGame.init(WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
 
    TheTextureManager.load("./Textures/As.bmp","tst",TheGame.getRenderer());
    
    while(TheGame.isRunning())
    {    
        TheGame.render();
        TheGame.handleEvents();
    }
    
    TheGame.clean();
    
    return 0;

}

