//Graphics for combat, 
#include "SDL/SDL.h"

int main( int argc, char* args[] )
{
    SDL_Surface * hello = NULL;
    SDL_Surface * screen = NULL;
    SDL_Init( SDL_INIT_EVERYTHING );

    screen = SDL_SetVideoMode(600,400,8,SDL_SWSURFACE);

    hello = SDL_LoadBMP("BMPTeste.bmp");

    SDL_BlitSurface (hello, NULL, screen, NULL);

    SDL_Flip( screen);

    SDL_Delay(2000);

    SDL_FreeSurface(hello);

    SDL_Quit();

    return 0;    
}
