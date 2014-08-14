//TextureManager header. Handles the storing and drawing of textures.
//Author: Vítor Fortes Rey

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SDL2/SDL.h"

#include <string>
#include <map>

#define TheTextureManager TextureManager::getInstance()


class TextureManager
{
    public:
        // Keep only one reference.
        static TextureManager& getInstance()
        {
            static TextureManager instance;
            return instance;
        }
        
        // Map for laoded textures. id -> texture.
        std::map<std::string, SDL_Texture*> textureMap;

        // Register fileName as id.
        bool load(std::string fileName,
            std::string id,
            SDL_Renderer* ptRenderer);

        
        // Simply draw an image.
        void draw(std::string id,
            int x, int y,
            int srcx, int srcy,
            int width, int height,
            SDL_Renderer* ptRenderer,
            SDL_RendererFlip flip = SDL_FLIP_NONE);
        
        
    private:
        TextureManager() {}                    // Keep private.  
        TextureManager(TextureManager const&);  // Don't Implement.
        void operator=(TextureManager const&); // Don't implement.
 };



#endif /* TEXTURE_MANAGER_H */
