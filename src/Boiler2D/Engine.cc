#include <Boiler2D/Engine.h>

Engine::Engine()
{
    mCurScreen = NULL; 
    mWindow = NULL;
    mRenderer = NULL; 
    mMustExit = false;
    mChangeScreen = false;
    mNewScreen = NULL;

    if(SDL_Init( SDL_INIT_EVERYTHING ) < 0)
    {
        printf("Cannot start sdl\n");
        ::exit(-1);
    }

    if(IMG_Init( IMG_INIT_PNG ) < 0 ) 
    {
        printf("Cannot start sdl_image\n");
        ::exit(-1);
    }

    mWindow = SDL_CreateWindow("Boiler2D", 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, 
            SDL_WINDOW_SHOWN); 

    if(mWindow == NULL)
        ::exit(-1);

    mRenderer = SDL_CreateRenderer( mWindow, -1, 
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    if(mRenderer == NULL) 
    {
        printf("Cannot start hw accel rendering\n");
        ::exit(-1);
    }
    SDL_SetRenderDrawColor( mRenderer, 0, 0, 0, 0xFF );
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" );

    sTextRenderer->load();
}

void Engine::shutdown()
{
    if(mWindow != NULL) 
    {
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        IMG_Quit();
        sTextRenderer->unload();
        SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
        SDL_Quit();
        setScreen(NULL);
        mWindow = NULL;
    } 
}

void Engine::dispatchEvent(SDL_Event *e) 
{
    int x, y;
    if(mCurScreen == NULL)
        return;

    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONUP ||
       e->type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState( &x, &y );
        std::pair<float,float> mc = Utils::screenToWorld(x, y);
        MouseEvent mouse = e->type == SDL_MOUSEMOTION ? MOUSE_MOVE :
                            e->type == SDL_MOUSEBUTTONUP ? MOUSE_UP :
                            MOUSE_DOWN;
        mCurScreen->onMouseEvent(mouse, mc.first, mc.second);
    }

    if(e->type == SDL_KEYDOWN || e->type == SDL_KEYUP)
    {
        KBDEvent kbd;
        kbd = (e->type == SDL_KEYDOWN) ? KBD_DOWN : KBD_UP;
        mCurScreen->onKeyboardEvent(kbd, e->key.keysym.sym);
    }
}

void Engine::run() 
{
    SDL_Event e;
    while(!mMustExit)
    {
        // Handle screen swap gracefully
        if(mChangeScreen) 
        {
            mChangeScreen = false;
            if(mCurScreen != NULL && mDeleteScreen)
                delete mCurScreen; 

            mCurScreen = mNewScreen;
            if(mCurScreen != NULL)
                mCurScreen->onLoad();
        }

        while(!mMustExit && SDL_PollEvent( &e ) != 0) 
        {
            if(e.type == SDL_QUIT) 
                mMustExit = true;
            else
                dispatchEvent(&e);
        }

        // Catch SDL_QUIT
        if(mMustExit) 
            break;

        if(mCurScreen != NULL)
        {
            mCurScreen->update(0.02f); 

            SDL_RenderClear( mRenderer );
            mCurScreen->render(0.02f);
            SDL_RenderPresent( mRenderer );
        }
        SDL_Delay(20);
    }

    shutdown();
}

void Engine::renderSprite(SpriteAnchor anchor, int id, float x, 
                          float y, float size, float speed)
{
    ImageSprite *sprite = sSpriteManager->get(id);
    std::pair<float,float> sz = Utils::tileSize();

    float sx = sprite->getWidth(), sy = sprite->getHeight();
    float rx = size, ry = size;
    if(sx < sy)
        ry *= (sy / sx);
    else
        rx *= (sx / sy);

    float xanch = x - (anchor & 0x0f) * (sz.second * 0.5f * rx);
    float yanch = y - (anchor >> 4) * (sz.second * 0.5f * ry);

    // coords in screen space
    std::pair<int,int> p = Utils::worldToScreen(xanch, yanch);

    // screen size
    std::pair<int,int> s = Utils::worldToScreenSize(
            sz.first * rx, 
            sz.second * ry);

    SDL_Rect dest = { p.first, p.second, s.first, s.second };
    SDL_Rect src = sprite->getRect(speed);

    SDL_RenderCopy( mRenderer, sprite->getTexture(), &src, &dest ); 
}
