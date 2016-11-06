#include "Engine.h"

Engine::Engine()
{
    mCurScreen = NULL; 
    mWindow = NULL;
    //mSurface = NULL;
    mRenderer = NULL; 
    mMustExit = false;

    if(SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf("Cannot start sdl\n");
        ::exit(-1);
    }

    if(IMG_Init( IMG_INIT_PNG ) < 0 ) 
    {
        printf("Cannot start sdl_image\n");
        ::exit(-1);
    }

    if(TTF_Init() == -1) {
        printf("Cannot start sdl_ttf\n");
        ::exit(-1);
    }

    mWindow = SDL_CreateWindow("Microgue", 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, 
            SDL_WINDOW_SHOWN); 

    if(mWindow == NULL)
        ::exit(-1);

    //mSurface = SDL_GetWindowSurface( mWindow );

    mRenderer = SDL_CreateRenderer( mWindow, -1, 
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    if(mRenderer == NULL) 
    {
        printf("Cannot start hw accel rendering\n");
        ::exit(-1);
    }
    SDL_SetRenderDrawColor( mRenderer, 0, 0, 0, 0xFF );
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

    sTextRenderer->load();
}

void Engine::shutdown() {
    if(mWindow != NULL) 
    {
        SDL_DestroyWindow( mWindow );  
        IMG_Quit();
        SDL_Quit();
        mWindow = NULL;
        setScreen(NULL);
    } 
}

void Engine::run() 
{
    SDL_Event e;
    while(!mMustExit)
    {
        while(SDL_PollEvent( &e ) != 0) 
        {
            if(e.type == SDL_QUIT) 
            {
                mMustExit = true;
                break;
            } 
            else if(mCurScreen != NULL) 
            {
                if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN 
                                             || e.type == SDL_MOUSEBUTTONUP) 
                {
                    int x, y;
                    SDL_GetMouseState( &x, &y );
                    std::pair<float,float> mc = Utils::screenToWorld(x, y);
                    MouseButtons evx;
                    switch(e.type) 
                    {
                        case SDL_MOUSEMOTION: evx = MOUSE_MOVE; break;
                        case SDL_MOUSEBUTTONUP: evx = MOUSE_UP; break;
                        case SDL_MOUSEBUTTONDOWN: evx = MOUSE_DOWN; break;
                        default: evx = MOUSE_NONE; break;
                    }
                    mCurScreen->onMouseEvent(evx, mc.first, mc.second);
                }
            }
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

void Engine::renderSprite(SpriteAnchor anchor, int id, float x, float y, float size)
{
    Sprite *sprite = sSpriteManager->get(id);
    std::pair<float,float> sz = Utils::tileSize();

    float sx = sprite->getWidth(), sy = sprite->getHeight();
    float rx = size, ry = size;
    if(sx < sy)
        ry *= (sy / sx);
    else
        rx *= (sx / sy);

    float xanch = x - (anchor & 0x0f) * (sz.second * 0.5f * rx);
    float yanch = y + (anchor >> 4) * (sz.second * 0.5f * ry);

    // coords in screen space
    std::pair<int,int> p = Utils::worldToScreen(xanch, yanch);

    // screen size
    std::pair<int,int> s = Utils::worldToScreenSize(
            sz.first * rx, 
            sz.second * ry);

    SDL_Rect dest = { p.first, p.second, s.first, s.second };
    SDL_Rect src = sprite->getRect();

    SDL_RenderCopy( mRenderer, sprite->getTexture(), &src, &dest ); 
}
