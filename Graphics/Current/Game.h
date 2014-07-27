//Game object header. Handles the game loop.
//Author: Vítor Fortes Rey
#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "TextureManager.h"

#define TheGame Game::getInstance()

class Game
{
    public:
         // Keep only one reference.
        static Game& getInstance()
        {
            static Game instance;
            return instance;
        }
        
        bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
        void render();
        void update();
        void handleEvents();
        void clean();
        
        bool isRunning() { return running; }
        SDL_Renderer* getRenderer() { return ptRenderer; }
        

    private:
        Game() : running(false)  {}  // Keep private.  
        Game(Game const&);           // Don't Implement.
        void operator=(Game const&); // Don't implement.
    
    
        SDL_Window* ptWindow;
        SDL_Renderer* ptRenderer;
        
        bool running;
};



#endif /* GAME_H */
