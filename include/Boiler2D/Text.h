#ifndef BOILER2D_TEXT_H
#define BOILER2D_TEXT_H

#include "Common.h"
#include "Config.h"
#include "Sprite.h"

class TextRenderer
{
public:
    static TextRenderer *instance()
    {
        static TextRenderer g; 
        return &g; 
    }

    // da chiamare una sola volta all'avvio del programma
    void load();
    void unload();

    // "ciao" -> Texture (da tenere in memoria o cancellare con clean
    TextSprite* draw(Fonts font, const std::string& text);
    TextSprite* drawSlow(Fonts font, const std::string& text);

    void free(TextSprite *font)
    {
        if(font != NULL)
            delete font;
    }
private:
    std::vector<TTF_Font *> mFonts;

    TextRenderer()
    {
        mFonts.resize(FONT_NULL); 
    }

    ~TextRenderer()
    {
        unload();
    }

    void loadFont(int id, TTF_Font *font)
    {
        if(font == NULL)
            return;

        mFonts[id] = font;
    }

    TextRenderer(const TextRenderer&) = delete;
    TextRenderer(TextRenderer&&) = delete;
    TextRenderer& operator=(const TextRenderer&) & = delete;
    TextRenderer& operator=(TextRenderer&&) & = delete;
};

#define sTextRenderer TextRenderer::instance()

#endif /* ifndef BOILER2D_TEXT_H */
