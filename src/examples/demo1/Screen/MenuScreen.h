#ifndef BOILER2D_EXAMPLE_SCREEN_MENU_H
#define BOILER2D_EXAMPLE_SCREEN_MENU_H

#include <Boiler2D/Common.h>
#include <Boiler2D/Screen.h>
#include <Boiler2D/Engine.h>
#include <Boiler2D/Config.h>
#include <Boiler2D/SpriteManager.h>
#include <Boiler2D/SpriteRenderer.h>
#include <Boiler2D/Text.h>
#include "GameScreen.h"
#include "BridgeScreen.h"

class MenuScreen : public Screen 
{
public:
    void onLoad()
    {
        // aggiungi voci menu
        sSpriteManager->load(SPRITE_FIRE);
#define TEXT(f,t) sTextRenderer->drawSlow(FONT_##f##SHERWOOD, t)
        mLogo = new SpriteRenderer(TEXT(B, "Boiler2D"), Color(160, 0, 0), 
                0, 0.7f, 1.0f, ANCHOR_CENTER, true);
        mPlay = new SpriteRenderer(TEXT(S, "New Run"),  Color(128, 128, 128), 
                0, 0.1f, 1.0f, ANCHOR_CENTER, true);
        mBridge = new SpriteRenderer(TEXT(S, "Bridge"),  Color(128, 128, 128), 
                0,-0.1f, 1.0f, ANCHOR_CENTER, true);
        mQuit = new SpriteRenderer(TEXT(S, "Quit"),     Color(128, 128, 128), 
                0,-0.3f, 1.0f, ANCHOR_CENTER, true);
#undef TEXT
    }

    virtual ~MenuScreen()
    {
        // cancella memoria allocata 
        delete mLogo;
        delete mPlay;
        delete mBridge;
        delete mQuit;
    }

    virtual void onMouseEvent(MouseEvent event, float x, float y)
    {
#define CHECK(btn,f) \
        if(Utils::inBoundingBox(btn->getBoundingBox(), x, y)) { \
            btn->setColor(Color(192,64,64)); \
            if(event == MOUSE_DOWN) { f(); } \
        } else \
            btn->setColor(Color(128,128,128));

        CHECK(mPlay, onPlay);
        CHECK(mBridge, onBridge);
        CHECK(mQuit, onQuit);
#undef CHECK
    }

    virtual void onKeyboardEvent(KBDEvent event, SDL_Keycode key)
    {
    }

    void onPlay() {
        sEngine->setScreen(new GameScreen, true);
    }

    void onBridge() {
        sEngine->setScreen(new BridgeScreen, true);
    }

    void onQuit() {
        sEngine->exit();
    }

    virtual void update(float dt)
    {
    
    }

    virtual void render(float dt)
    {
        sEngine->renderSprite(ANCHOR_BOTTOMRIGHT, SPRITE_FIRE, Utils::ratio(), -1.3f, 6.0f); 
        sEngine->renderSprite(ANCHOR_BOTTOMLEFT, SPRITE_FIRE,-Utils::ratio(), -1.3f, 6.0f); 

        mLogo->render();
        mPlay->render();
        mBridge->render();
        mQuit->render();
    }
private:
    SpriteRenderer *mLogo, *mPlay, *mQuit, *mBridge;
};

#endif /* ifndef BOILER2D_EXAMPLE_SCREEN_MENU_H */
