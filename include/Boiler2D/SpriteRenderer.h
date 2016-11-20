#ifndef BOILER2D_SPRITE_RENDERER_H
#define BOILER2D_SPRITE_RENDERER_H

#include "Common.h"
#include "Text.h"
#include "Utils.h"
#include "Engine.h"
#include "Geometry.h"

namespace Boiler2D
{

class SpriteRenderer {
public:
    SpriteRenderer(TextSprite *sprite, Color color, float x, float y, 
                   float zoom = 1.0f, SpriteAnchor anchor = ANCHOR_CENTER, 
                   bool spriteOwner = false) : mColor(color)
    {
        mAnchor = anchor;
        mSprite = sprite;
        mZoom = zoom;
        setX(x);
        setY(y);
        mSpriteOwner = spriteOwner;
    }

    ~SpriteRenderer()
    {
        if(mSpriteOwner && mSprite != NULL)
            delete mSprite;
    }

    FloatRect getBoundingBox() const 
    {
        std::pair<float,float> s = 
            Utils::screenToWorldSize(mSprite->getWidth(), mSprite->getHeight());
        return FloatRect(mX, mY, s.first, s.second); 
    }

    void setColor(Color c)
    {
        mColor = c;
    }

    void setX(double x)
    {
        std::pair<double,double> w = Utils::screenToWorldSize(
                mSprite->getWidth(), mSprite->getHeight());
        mX = x - (mAnchor & 0x0f) * (w.first / 2.0f); 
    }

    void setY(double y)
    {
        std::pair<double,double> w = Utils::screenToWorldSize(
                mSprite->getWidth(), mSprite->getHeight());
        mY = y - (mAnchor >> 4) * (w.second / 2.0f);
    }

    void render()
    {
        // coords in screen space
        std::pair<int,int> p = Utils::worldToScreen(mX, mY);

        SDL_Rect dest = { p.first, p.second, 
            mSprite->getWidth(), mSprite->getHeight() };

        SDL_SetTextureColorMod(mSprite->getTexture(), mColor.r, mColor.g, mColor.b);
        SDL_RenderCopy( sEngine->getRenderer(), mSprite->getTexture(), NULL, &dest ); 
        SDL_SetTextureColorMod(mSprite->getTexture(), 255, 255, 255);
    }
private:
    SpriteAnchor mAnchor;
    Color mColor;
    float mZoom, mX, mY;
    TextSprite *mSprite;
    bool mSpriteOwner;
};


} /* Boiler2D */

#endif /* ifndef BOILER2D_SPRITE_RENDERER_H */
