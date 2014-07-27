//Graphics header
//Author: Nicolas Silveira Kagami

#include "SDL2/SDL.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 480 
#define WINDOW_TITLE "Main Window (so far...)"

#define MAP_MAX_HEIGHT 20
#define MAP_MAX_WIDTH 15

/*
class Tile
{
    public:
       int type;
       //Combatant * occupant;

       void print_type();
       Tile();
       Tile(int kind);
};
class Map
{
    public:
        Tile * tiles; 
        int height;
        int width;
        //Window * z
        //std::vector <Combatant> contenders;
        
        void print_ascii();
        Map(int x, int y);
        ~Map();
};
class Texture
{ 
    public:
        SDL_Texture * img;
        std::string filename;

        Texture(std::string &file);
        static std::vector <Texture> textures;
};
class Window
{
    public:
        SDL_Window * window;
        SDL_Surface* screen;
        SDL_Renderer * renderer;
        SDL_Event * mainEvent;
        bool running;

        Window();
        ~Window();
        void run();
        int present_image(std::string &name);
        void renderTexture(SDL_Texture *tex, int x, int y);
};*/
