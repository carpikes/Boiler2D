#ifndef BOILER2D_SPRITE_H
#define BOILER2D_SPRITE_H

#include "Common.h"
#include "Config.h"
#include "Image.h"

class Sprite
{
public:
    virtual ~Sprite() {}
    virtual int getWidth() const 
    { 
        return mWidth;
    }
    virtual int getHeight() const 
    { 
        return mHeight;
    }
    virtual SDL_Texture *getTexture() = 0;
protected:
    int mWidth, mHeight;
};

class ImageSprite : public Sprite
{
public:
    ImageSprite(Image *img, const spriteinfo_t& info) : 
        mImage(img), mInfo(info)
    {
        mCurN = 0;
        mStartTime = SDL_GetTicks();
        mImage->incrementUsageCount(); 
        mWidth = mImage->getInfo().tilew;
        mHeight = mImage->getInfo().tileh;
    }

    ~ImageSprite()
    {
        mImage->decrementUsageCount();
    }

    // Ottiene la posizione nella spritesheet
    SDL_Rect getRect()
    {
        const sheetinfo_t& imgInfo = mImage->getInfo();

        if(mInfo.flags & SPRITEFLAG_ANIMATED)
        {
            mCurN = SDL_GetTicks() / mInfo.time;
            if(mCurN >= mInfo.count)
            {
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

    SDL_Texture *getTexture()
    {
        return mImage->getTexture();
    }
private:
    Image *mImage;
    const spriteinfo_t mInfo;
    int mCurN;
    uint32_t mStartTime;
};

class TextSprite : public Sprite
{
    friend class TextRenderer;
public:
    ~TextSprite()
    {
        SDL_DestroyTexture(mTexture); 
    }

    SDL_Texture *getTexture()
    {
        return mTexture; 
    }
private:
    SDL_Texture *mTexture;

    TextSprite(const TextSprite&) = delete;
    TextSprite(TextSprite&&) = delete;
    TextSprite& operator=(const TextSprite&) & = delete;
    TextSprite& operator=(TextSprite&&) & = delete;

    TextSprite(SDL_Texture *texture, int w, int h) : mTexture(texture)
    { 
        mWidth = w;
        mHeight = h;
    }
};

#endif /* ifndef BOILER2D_SPRITE_H */
