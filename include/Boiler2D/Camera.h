#ifndef BOILER2D_CAMERA_H
#define BOILER2D_CAMERA_H

#include "Common.h"
#include "Utils.h"
#include "Geometry.h"
#include "Sprite.h"
#include "Engine.h"

namespace Boiler2D
{

class Camera
{
public:
    Camera()
    {
        mZoom = 10.0f;
        mRatio = Utils::ratio();
        mWorldArea = FloatRect(0,0,1.0f,1.0f);
    }

    FloatRect getVisibleArea() const 
    {
        return FloatRect(mPos.x, mPos.y, mZoom * mRatio, mZoom);
    }

    void setWorldArea(const FloatRect& area)
    {
        mWorldArea = area; 
    }

    void centerOn(const FloatCoords& pos, bool instant = false)
    {
        mTargetPos = pos;
        if(instant)
            mPos = mTargetPos;
    }

    // tipo centerOn, ma si sposta solo se le pos sono > soglia
    void keepInbound(const FloatCoords& pos)
    {
        (void)pos; 
    }

    void update(float dt)
    {
        if(mTargetPos != mPos)
        {
            float dX = mTargetPos.x - mPos.x;
            float dY = mTargetPos.y - mPos.y;
            float dist = sqrt(dX * dX + dY * dY);
            if(fabs(dist) > 0.00001)
            {
                float ddx = dX / dist * dt;
                float ddy = dY / dist * dt;

                if(ddx > dX)
                    ddx = dX;
                if(ddy > dY)
                    ddy = dY;

                mPos.x += ddx;
                mPos.y += ddy;
            }
        }
    }

    FloatCoords getCoords() const { return mPos; }
    float getRatio() const { return mRatio; }
protected:
    float mZoom, mRatio;
    FloatCoords mPos, mTargetPos;
    FloatRect mWorldArea;
};

class TileRenderer
{
public:
    TileRenderer()
    {
        mCamera = Camera();
    }

    void renderTile(ImageSprite *tile, TileCoords t, float size = 1.0f)
    {
        std::pair<float,float> sz = Utils::tileSize();

        float sx = tile->getWidth(), sy = tile->getHeight();
        float rx = size, ry = size;
        if(sx < sy)
            ry *= (sy / sx);
        else
            rx *= (sx / sy);

        // coords in screen space
        std::pair<int,int> p = Utils::worldToScreen(t.x, t.y);

        // screen size
        std::pair<int,int> s = Utils::worldToScreenSize(
                sz.first * rx, 
                sz.second * ry);

        SDL_Rect dest = { p.first, p.second, s.first, s.second };
        SDL_Rect src = tile->getRect(1.0f);

        sEngine->render(tile, &src, &dest);
    }

    TileRect getVisibleArea() const
    {
        TileRect area; 
        FloatRect visible = mCamera.getVisibleArea();

        const float minScreenY = 0.f, maxScreenY = 1.1f;
        const float minScreenX = 0.f, maxScreenX = mCamera.getRatio() + 0.1f;

        area.x = std::max(0, (int)((minScreenX - visible.x)));
        area.y = std::max(0, (int)((minScreenY - visible.y)));

        area.w = (int)((maxScreenX - visible.x)) - area.x;
        area.h = (int)((maxScreenY - visible.y)) - area.y;
        return area;
    }
private:
    Camera mCamera;
};
    
} /* Boiler2D */ 

#endif /* ifndef BOILER2D_CAMERA_H */
