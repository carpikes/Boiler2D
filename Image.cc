#include "Image.h"
#include "Engine.h"

bool Image::load()
{
    assert(mTexture == NULL);
    SDL_Surface *s = IMG_Load(mName.c_str());
    if(s == NULL)
    {
        printf("Can't load %s\n", mName.c_str());
        return false;
    }
    SDL_Renderer *renderer = sEngine->getRenderer();
    mTexture = SDL_CreateTextureFromSurface(renderer, s);

    SDL_FreeSurface(s);
    if(mTexture == NULL) {
        printf("Can't create texture for %s\n", mName.c_str());
        return false;
    }
    return true;
}

void Image::unload() {
    if(mTexture != NULL)
        SDL_DestroyTexture(mTexture);
}
