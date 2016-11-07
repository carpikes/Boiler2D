#ifndef MICROGUE_SPRITE_H
#define MICROGUE_SPRITE_H

#include "Common.h"
#include "Config.h"
#include "Image.h"

class Sprite 
{
public:
    Sprite(Image *img, const spriteinfo_t& info) : mImage(img), mInfo(info)
    {
        mCurN = 0;
        mStartTime = SDL_GetTicks();
        mImage->incrementUsageCount(); 
    }

    ~Sprite()
    {
        mImage->decrementUsageCount();
    }

    inline int getWidth() const { return mImage->getInfo().tilew; }
    inline int getHeight() const { return mImage->getInfo().tileh; }
    
    // Ottiene la posizione nella spritesheet
    SDL_Rect getRect() {
        const sheetinfo_t& imgInfo = mImage->getInfo();

        if(mInfo.flags & SPRITEFLAG_ANIMATED) {
            mCurN = SDL_GetTicks() / mInfo.time;
            if(mCurN >= mInfo.count) {
                if(mInfo.flags & SPRITEFLAG_REPEAT) 
                    mCurN %= mInfo.count;
                else
                    mCurN = mInfo.count - 1;
            }
        }

        int x = (mInfo.n + mCurN) % mImage->getNSpritesX();
        int y = (mInfo.n + mCurN) / mImage->getNSpritesX();

        SDL_Rect a = { 
            x * imgInfo.tilew, 
            y * imgInfo.tileh, 
            imgInfo.tilew, 
            imgInfo.tileh
        };
        return a;
    }

    SDL_Texture *getTexture() {
        return mImage->getTexture();
    }
private:
    Image *mImage;
    const spriteinfo_t mInfo;
    int mCurN;
    uint32_t mStartTime;
};

#endif /* ifndef MICROGUE_SPRITE_H */
