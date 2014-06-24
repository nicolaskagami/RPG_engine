//Graphics header
//Author: Nicolas Silveira Kagami

#include "SDL2/SDL.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 480 
#define WINDOW_TITLE "Main Window (so far...)"

#define MAP_MAX_HEIGHT 20
#define MAP_MAX_WIDTH 15


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
};
class Window
{
    public:
        SDL_Window * window;
        SDL_Surface* screen;
        SDL_Renderer * renderer;
        SDL_Event * mainEvent;
        std::vector<Texture> textures;
        bool running;

        void logSDLError(std::ostream &os, const std::string &msg);
        int read_textures_list(std::string &texture_file);
        static int init();
        static void run();
        static void close();
        int present_image(std::string &name);
        SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
        void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
};
