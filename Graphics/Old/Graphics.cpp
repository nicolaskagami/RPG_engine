//Graphics implementation
//Author: Nicolas Silveira Kagami

#include <stdio.h>
#include <iostream>
#include "Graphics.h"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 480
#define WINDOW_TITLE "Test"

SDL_Window * window = NULL;
SDL_Surface * screen = NULL;
SDL_Surface * image = NULL;
SDL_Renderer * renderer = NULL;
SDL_Event * mainEvent = NULL;
SDL_Texture * a = NULL;
SDL_Texture * b = NULL;
bool running = true;

void logSDLError(std::ostream &os, const std::string &msg)
{
        os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != NULL)
    {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        //Make sure converting went ok too
        if (texture == NULL)
            logSDLError(std::cout, "CreateTextureFromSurface");
    }
    else
        logSDLError(std::cout, "LoadBMP");

    return texture;
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}
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
    image = SDL_LoadBMP ("image.bmp");
    
    SDL_BlitSurface(image,NULL,screen,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
    a = loadTexture("A.bmp",renderer);
    b = loadTexture("B.bmp",renderer);
    int w,h;
    SDL_QueryTexture(a,NULL,NULL,&w,&h);
    renderTexture(a,renderer,0,0);
    renderTexture(a,renderer,w,0);
    renderTexture(a,renderer,0,h);
    renderTexture(a,renderer,w,h);
    printf("W: %d, H: %d\n",w,h);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    while(running && mainEvent->type != SDL_QUIT)
    {
        SDL_PollEvent(mainEvent);
 //       SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete mainEvent;
    SDL_Quit();
    return 0;
}
