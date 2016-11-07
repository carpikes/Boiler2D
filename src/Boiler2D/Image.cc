#include <Boiler2D/Image.h>
#include <Boiler2D/Engine.h>

bool Image::load()
{
    assert(mTexture == NULL);
    SDL_Surface *s = IMG_Load(mInfo.file.c_str());
    if(s == NULL)
    {
        printf("Can't load %s: %s\n", mInfo.file.c_str(), SDL_GetError());
        return false;
    }
    SDL_Renderer *renderer = sEngine->getRenderer();

    assert(renderer != NULL);
    assert(s->w > 0 && s->h > 0);

    mNColumns = s->w / mInfo.tilew;
    mNRows = s->h / mInfo.tileh;

    mTexture = SDL_CreateTextureFromSurface(renderer, s);

    SDL_FreeSurface(s);
    if(mTexture == NULL) {
        printf("Can't create texture for %s: %s\n", mInfo.file.c_str(), 
                                                    SDL_GetError());
        return false;
    }
    printf("Loaded ssheet %s\n", mInfo.file.c_str());
    return true;
}

void Image::unload() {
    if(mTexture != NULL)
        SDL_DestroyTexture(mTexture);
}
