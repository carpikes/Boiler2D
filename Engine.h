#ifndef MICROGUE_ENGINE_H
#define MICROGUE_ENGINE_H

#include "Common.h"
#include "Config.h"
#include "Screen.h"
#include "Sprite.h"
#include "Screen/MenuScreen.h"
#include "Utils.h"

class Engine
{
public:
    static Engine *instance() { 
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
        if(mCurScreen != NULL && delete_old)
            delete mCurScreen; 

        mCurScreen = screen;
    }

    void renderSprite(Sprite *sprite, float x, float y) {
        std::pair<int,int> p = Utils::worldToScreen(x, y);
        int rw = sprite->getWidth(), rh = sprite->getHeight();

        SDL_Rect dest = { p.first, p.second, rw, rh };
        SDL_Rect src = sprite->getRect();

        SDL_RenderCopy( mRenderer, sprite->getTexture(), &src, &dest ); 
    }

    void exit() {
        mMustExit = true; 
    }

    void run()
    {
        assert(mWindow == NULL);

        if(!init())
            return;

        setScreen(new MenuScreen, true);

        SDL_Event e;
        while(!mMustExit)
        {
            while(SDL_PollEvent( &e ) != 0) {
                if(e.type == SDL_QUIT) {
                    mMustExit = true;
                    break;
                } else if(mCurScreen != NULL)
                    mCurScreen->onEvent(e);
            }

            if(mMustExit) // catturo l'exit dopo gli eventi
                break;

            if(mCurScreen != NULL)
                mCurScreen->update(0.02f); 

            SDL_RenderClear( mRenderer );
            if(mCurScreen != NULL)
                mCurScreen->render(0.02f);
            SDL_RenderPresent( mRenderer );
            //SDL_UpdateWindowSurface( mWindow );
            SDL_Delay(20);
        }

        shutdown();
    }
private:
    bool mMustExit;
    Screen *mCurScreen;
    SDL_Window* mWindow;
    //SDL_Surface* mSurface;
    SDL_Renderer* mRenderer;

    Engine()
    {
        mCurScreen = NULL; 
        mWindow = NULL;
        //mSurface = NULL;
        mRenderer = NULL; 
        mMustExit = false;
    }

    void shutdown() {
        if(mWindow != NULL) 
        {
            SDL_DestroyWindow( mWindow );  
            IMG_Quit();
            SDL_Quit();
            mWindow = NULL;
            setScreen(NULL);
        } 
    }

    bool init() {
        if(SDL_Init( SDL_INIT_VIDEO ) < 0)
        {
            printf("Cannot start sdl\n");
            return false;
        }

        if(IMG_Init( IMG_INIT_PNG ) < 0 ) 
        {
            printf("Cannot start sdl_image\n");
            return false;
        }

        mWindow = SDL_CreateWindow("Microgue", 
                SDL_WINDOWPOS_UNDEFINED, 
                SDL_WINDOWPOS_UNDEFINED, 
                SCREEN_WIDTH, SCREEN_HEIGHT, 
                SDL_WINDOW_SHOWN); 

        if(mWindow == NULL)
            return false;

        //mSurface = SDL_GetWindowSurface( mWindow );

        mRenderer = SDL_CreateRenderer( mWindow, -1, 
                    SDL_RENDERER_ACCELERATED );

        if(mRenderer == NULL) 
        {
            printf("Cannot start hw accel rendering\n");
            return false;
        }
        SDL_SetRenderDrawColor( mRenderer, 0, 0, 0, 0xFF );
        return true;
    }
};

#define sEngine Engine::instance()


#endif /* ifndef MICROGUE_ENGINE_H */
