//Graphics implementation
//Author: Nicolas Silveira Kagami

#include "Graphics.h"


Tile::Tile()
{
    type = 0;
}
Tile::Tile(int kind)
{
    type = kind;
}
void Tile::print_type()
{
    printf("%d",type);
}
Map::Map(int x, int y)
{
    if((x<=MAP_MAX_WIDTH)&&(y<=MAP_MAX_HEIGHT))
    {
        tiles = new Tile[x*y];
        height = y;
        width = x;
    }
    else
    {
        printf("Map not created: Maximum parameters:\n Height: %d\tWidth: %d\n",
                MAP_MAX_HEIGHT,MAP_MAX_WIDTH);
        exit(0);
    }
}
Map::~Map()
{
    delete tiles;
}
void Map::print_ascii()
{
    int i,j;
    printf("Printing map(%d,%d)\n",height,width);
    for(i=0;i<width;i++)
    {
        for(j=0;j<height;j++)
            tiles[i*height+j].print_type();
        printf("\n");
    }
}

Texture::Texture(std::string &file)
{
    filename = file;
}
void Window::logSDLError(std::ostream &os, const std::string &msg)
{
        os << msg << " error: " << SDL_GetError() << std::endl;
}
int Window::read_textures_list(std::string &texture_file)
{
    std::string line;
    Texture * newTexture;
    std::ifstream textfile (texture_file, std::ifstream::in);
    if(textfile.is_open())
    {
        while(getline(textfile,line))
        {
            newTexture = new Texture(line);
            textures.push_back(newTexture);
        }
        textfile.close();
        return 0;
    }
    else
        return -1;
}
SDL_Texture* Window::loadTexture(const std::string &file)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != NULL)
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        if (texture == NULL)
            logSDLError(std::cout, "CreateTextureFromSurface");
    }
    else
        logSDLError(std::cout, "LoadBMP");

    return texture;
}
void Window::renderTexture(SDL_Texture *tex, int x, int y)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, tex, NULL, &dst);
}
int Window::init()
{ 
    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        logSDLError(std::cout,"Initialization");
        exit(0);
    }
    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if( window == NULL)
    {
        logSDLError(std::cout,"Creating Window");
        exit(0);
    }

    running = true;

    screen = SDL_GetWindowSurface( window );
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    mainEvent = new SDL_Event();
    num_textures=0;

    a = loadTexture("A.bmp",renderer);
    b = loadTexture("B.bmp",renderer);
    SDL_QueryTexture(a,NULL,NULL,&w,&h);
}
void Window::run()
{
    while(running && mainEvent->type != SDL_QUIT)
    {
        SDL_PollEvent(mainEvent);
 //       SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}
void Window::close()
{
    SDL_DestroyTexture(a);
    SDL_DestroyTexture(b);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete mainEvent;
    SDL_Quit();
}
int Window::present_image(std::string &name)
{
    SDL_Surface * image = SDL_LoadBMP (name);
    if(image)
    {
        SDL_BlitSurface(image,NULL,screen,NULL);
        SDL_UpdateWindowSurface(window);
    }
}
