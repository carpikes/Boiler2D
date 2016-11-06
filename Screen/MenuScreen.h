#ifndef MICROGUE_SCREEN_MENU_H
#define MICROGUE_SCREEN_MENU_H

#include "../Common.h"
#include "../Screen.h"
#include "../Engine.h"
#include "../Config.h"
#include "../SpriteManager.h"
#include "../SpriteRenderer.h"
#include "../Text.h"

class MenuScreen : public Screen 
{
public:
    void onLoad()
    {
        // aggiungi voci menu
        sSpriteManager->load(SPRITE_FIRE);
#define TEXT(f,t) sTextRenderer->drawSlow(FONT_##f##SHERWOOD, t)
        mLogo = new SpriteRenderer(TEXT(B, "MICROGUE"), Color(160, 0, 0), 
                0, 0.7f, 1.0f, ANCHOR_CENTER, true);
        mPlay = new SpriteRenderer(TEXT(S, "New Run"),  Color(128, 128, 128), 
                0, 0.1f, 1.0f, ANCHOR_CENTER, true);
        mQuit = new SpriteRenderer(TEXT(S, "Quit"),     Color(128, 128, 128), 
                0,-0.1f, 1.0f, ANCHOR_CENTER, true);
#undef TEXT
    }

    virtual ~MenuScreen()
    {
        // cancella memoria allocata 
        delete mLogo;
        delete mPlay;
        delete mQuit;
    }

    virtual void onMouseEvent(MouseButtons buttons, float x, float y)
    {
#define CHECK(btn,f) \
        if(Utils::inBoundingBox(btn->getBoundingBox(), x, y)) { \
            btn->setColor(Color(192,64,64)); \
            if(buttons == MOUSE_DOWN) { f(); } \
        } else \
            btn->setColor(Color(128,128,128));

        CHECK(mPlay, onPlay);
        CHECK(mQuit, onQuit);
#undef CHECK
    }

    void onPlay() {
        printf("Play\n"); 
    }

    void onSetting() {
        printf("Settings\n"); 
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
        mQuit->render();
    }
private:
    SpriteRenderer *mLogo, *mPlay, *mQuit;
};

#endif /* ifndef MICROGUE_SCREEN_MENU_H */
