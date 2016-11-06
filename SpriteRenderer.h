#ifndef MICROGUE_SPRITE_RENDERER_H
#define MICROGUE_SPRITE_RENDERER_H

#include "Common.h"
#include "Text.h"
#include "Utils.h"
#include "Engine.h"

class SpriteRenderer {
public:
    SpriteRenderer(FontTexture *sprite, Color color, float x, float y, 
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

    Rect getBoundingBox() const 
    {
        std::pair<float,float> s = 
            Utils::screenToWorldSize(mSprite->getWidth(), mSprite->getHeight());
        Rect out = { mX, mY, s.first, s.second }; 
        return out;
    }

    void setColor(Color c)
    {
        mColor = c;
    }

    void setX(float x)
    {
        std::pair<float,float> w = Utils::screenToWorldSize(
                mSprite->getWidth(), mSprite->getHeight());
        mX = x - (mAnchor & 0x0f) * (w.first / 2.0f); 
    }

    void setY(float y)
    {
        std::pair<float,float> w = Utils::screenToWorldSize(
                mSprite->getWidth(), mSprite->getHeight());
        mY = y + (mAnchor >> 4) * (w.second / 2.0f);
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
    FontTexture *mSprite;
    bool mSpriteOwner;
};

#endif /* ifndef MICROGUE_SPRITE_RENDERER_H */
