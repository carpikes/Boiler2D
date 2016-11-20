#ifndef BOILER2D_ENGINE_H
#define BOILER2D_ENGINE_H

#include "Common.h"
#include "Config.h"
#include "Screen.h"
#include "Sprite.h"
#include "Utils.h"
#include "Text.h"
#include "SpriteManager.h"

namespace Boiler2D
{

class Engine
{
public:
    inline static Engine *instance() { 
        static Engine g; 
        return &g; 
    }

    Screen *getScreen() 
    { 
        return mCurScreen; 
    }

    SDL_Renderer *getRenderer() 
    { 
        return mRenderer;
    }

    void setScreen(Screen *screen, bool delete_old = true)
    {
        if(mCurScreen == screen)
            return;
        assert(mChangeScreen == false);

        mNewScreen = screen;
        mDeleteScreen = delete_old;
        mChangeScreen = true;
    }

    void renderSprite(SpriteAnchor anchor, int id, float x, float y, float size, float speed = 1.0f);

    void exit() 
    {
        mMustExit = true; 
    }

    void run();

    void render(ImageSprite *tile, const SDL_Rect* src, const SDL_Rect* dest) 
    {
        SDL_RenderCopy(mRenderer, tile->getTexture(), src, dest);
    }
private:
    bool mChangeScreen, mDeleteScreen;
    Screen *mNewScreen;

    bool mMustExit;
    Screen *mCurScreen;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    Engine();
    void shutdown();
    void dispatchEvent(SDL_Event *e);

    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) & = delete;
    Engine& operator=(Engine&&) & = delete;
};

#define sEngine Engine::instance()



} /* Boiler2D */

#endif /* ifndef BOILER2D_ENGINE_H */
