#ifndef MICROGUE_SPRITE_H
#define MICROGUE_SPRITE_H

#include "Common.h"
#include "Config.h"
#include "Image.h"

class Sprite {
public:
    Sprite(Image *img, const spriteinfo_t& info) : mImage(img), mInfo(info) 
    {
        mImage->incrementUsageCount(); 
    }

    ~Sprite()
    {
        mImage->decrementUsageCount();
    }

    inline int getWidth() const { return mInfo.w; }
    inline int getHeight() const { return mInfo.h; }
    
    SDL_Rect getRect() {
        SDL_Rect a = { mInfo.x, mInfo.y, mInfo.w, mInfo.h };
        return a;
    }
    SDL_Texture *getTexture() {
        return mImage->getTexture();
    }
private:
    Image *mImage;
    const spriteinfo_t mInfo;
};


#endif /* ifndef MICROGUE_SPRITE_H */
