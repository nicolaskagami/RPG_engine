//Graphics implementation
//Author: Nicolas Silveira Kagami

#include <stdio.h>
#include "Graphics.h"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 480
#define WINDOW_TITLE "Test"

SDL_Window * window = NULL;
SDL_Surface * screen = NULL;
SDL_Surface * image = NULL;
SDL_Renderer * renderer = NULL;
SDL_Event * mainEvent = NULL;
bool running = true;

int init()
{ 
    SDL_Surface* screen = NULL;
    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf("SDL2 Error: Could not initialize\n");
        exit(0);
    }
    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if( window == 0)
    {
        printf("SDL2 Error: Could not create window\n");
        exit(0);
    }

    screen = SDL_GetWindowSurface( window );
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    mainEvent = new SDL_Event();
    
    while(running && mainEvent->type != SDL_QUIT)
    {
        SDL_PollEvent(mainEvent);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    //image = SDL_LoadBMP ("")
    //SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete mainEvent;
    SDL_Quit();
    return 0;
}
