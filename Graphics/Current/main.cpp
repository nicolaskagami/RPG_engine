//Main tester for Graphics
//Author: Nicolas Silveira Kagami

#include <stdio.h>
#include "Graphics.h"


int main(int argc, char ** arv)
{
    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf("SDL Error: Initialization\n");
        exit(0);
    }
    Window w;
    Map hehe(5,5);
    hehe.print_ascii();
    SDL_Quit();
}
