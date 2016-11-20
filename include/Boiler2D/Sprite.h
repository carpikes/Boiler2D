#ifndef BOILER2D_SPRITE_H
#define BOILER2D_SPRITE_H

#include "Common.h"
#include "Config.h"
#include "Image.h"

namespace Boiler2D
{

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
        mOffset = 0;
        mLastSpeed = 0;
    }

    ~ImageSprite()
    {
        mImage->decrementUsageCount();
    }

    // Ottiene la posizione nella spritesheet
    SDL_Rect getRect(float speed)
    {
        const sheetinfo_t& imgInfo = mImage->getInfo();

        if(mInfo.flags & SPRITEFLAG_ANIMATED)
        {
            bool updateSpeed = true;
            float rSpeed = speed;
            //if(speed == 0 && mLastSpeed != 0)
            //    rSpeed = mLastSpeed;
            mCurN = SDL_GetTicks() / mInfo.time * rSpeed + mOffset;

            // in caso di cambio di velocita`, tengo costante la fase
            if(mLastSpeed != speed && mLastSpeed != 0)
            {
                int realN = SDL_GetTicks() / mInfo.time * mLastSpeed + mOffset;
                mOffset += realN - mCurN;  // ... aggiungendo dell'offset
                mCurN = realN;
            }

            // cerco di far resettare l'animazione gracefully (al primo loop)
            /*
            if(mLastSpeed != 0 && speed == 0)
            {
                int turns = mCurN / mInfo.count;
                if(mInfo.count != 1)
                    printf("%f->%f %d\n", mLastSpeed, speed, turns);
                if(turns > mTurns || mCurN == 0)
                {
                    printf("McurN = 0\n");
                    mCurN = 0;
                    mLastN = 0;
                    mOffset = 0;
                } else
                    updateSpeed = false;
            }
            */

            if(mCurN >= mInfo.count)
            {
                if(mInfo.flags & SPRITEFLAG_REPEAT) 
                {
                    mTurns = mCurN / mInfo.count;
                    mCurN %= mInfo.count;
                } else
                    mCurN = mInfo.count - 1;
            }

            mLastN = mCurN;
            if(updateSpeed)
                mLastSpeed = speed;
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

    // questi due sono per tenere in sync l'animazione
    // con il cambio di velocita`
    float mLastSpeed;
    int mLastN, mTurns; //mTurns e` per fare l'animazione di fine quando speed -> 0
    int mOffset = 0;
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


} /* Boiler2D */

#endif /* ifndef BOILER2D_SPRITE_H */
