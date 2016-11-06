#ifndef MICROGUE_TEXT_H
#define MICROGUE_TEXT_H

#include "Common.h"
#include "Config.h"

class FontTexture
{
public:
    FontTexture(SDL_Texture *texture, int w, int h) : mTexture(texture),
            mWidth(w), mHeight(h) 
    { }

    ~FontTexture()
    {
        SDL_DestroyTexture(mTexture); 
    }

    SDL_Texture *getTexture()
    {
        return mTexture; 
    }

    int getWidth() const { return mWidth; }
    int getHeight() const { return mHeight; }
private:
    SDL_Texture *mTexture;
    int mWidth, mHeight;

    FontTexture(const FontTexture&) = delete;
    FontTexture(FontTexture&&) = delete;
    FontTexture& operator=(const FontTexture&) & = delete;
    FontTexture& operator=(FontTexture&&) & = delete;
};

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

    // "ciao" -> Texture (da tenere in memoria o cancellare con clean
    FontTexture* draw(Fonts font, const std::string& text);
    FontTexture* drawSlow(Fonts font, const std::string& text);

    void free(FontTexture *font) {
        if(font != NULL)
            delete font;
    }
private:
    std::vector<TTF_Font *> mFonts;

    TextRenderer()
    {
        mFonts.resize(FONT_NULL); 
    }

    ~TextRenderer() {
        for(TTF_Font * f : mFonts) 
        {
            if(f != NULL)
                TTF_CloseFont(f);
        } 
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

#endif /* ifndef MICROGUE_TEXT_H */
