//TextureManager implementation. Handles the storing and drawing of textures.
#include "TextureManager.h"


bool TextureManager::load(std::string fileName,
        std::string id, SDL_Renderer* ptRenderer)
{
    // load surface from file.
    // IMG_Load???
    SDL_Surface* ptTempSurface = SDL_LoadBMP(fileName.c_str());
    if(ptTempSurface == 0)
    {
        return false;
    }
    
    // make it a texture.
    SDL_Texture* ptTexture = SDL_CreateTextureFromSurface(ptRenderer, ptTempSurface);
    SDL_FreeSurface(ptTempSurface);
    
    // everything went ok, add the texture to our list
    if(ptTexture != 0)
    {
        textureMap[id] = ptTexture;
        return true;
    }
    // reaching here means something went wrong
    return false;
}

void TextureManager::draw(std::string id,
            int x, int y,
            int srcx, int srcy,
            int width, int height,
            SDL_Renderer* ptRenderer,
            SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = srcx;
    srcRect.y = srcy;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_RenderCopyEx(ptRenderer, textureMap[id], &srcRect,
        &destRect, 0, 0, flip);
}
