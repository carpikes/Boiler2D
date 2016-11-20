#include <Boiler2D/Text.h>
#include <Boiler2D/Engine.h>

namespace Boiler2D
{

void TextRenderer::unload()
{
    if(TTF_WasInit())
    {
        for(TTF_Font * f : mFonts) 
        {
            if(f != NULL)
                TTF_CloseFont(f);
        } 

        TTF_Quit();
    }
}

void TextRenderer::load()
{
    if(TTF_WasInit())
        return;

    if(TTF_Init() == -1)
    {
        printf("Cannot start sdl_ttf\n");
        ::exit(-1);
    }

    int i = 0;
    while(the_fonts[i].id != FONT_NULL) 
    {
        const fontsinfo_t& f = the_fonts[i];
        TTF_Font *font = TTF_OpenFont(f.file.c_str(), the_fonts[i].size);
        if(font == NULL)
        {
            printf("Cannot load font %s\n", f.file.c_str());
            exit(-1);
        }

        printf("Loading font %s\n", f.file.c_str());
        loadFont(f.id, font);

        //TTF_CloseFont(font);
        i++;
    }
}

TextSprite *TextRenderer::draw(Fonts font, const std::string& text)
{
    SDL_Surface *surface;
    if(font >= FONT_NULL)
        return NULL;

    SDL_Color white = {255,255,255,255};
    surface = TTF_RenderText_Solid(mFonts[font], text.c_str(), white);
    if(surface == NULL)
    {
        printf("Cannot render text\n");
        return NULL;
    }

    SDL_Texture *t = SDL_CreateTextureFromSurface(sEngine->getRenderer(), 
        surface ); 

    TextSprite *ret = new TextSprite(t, surface->w, surface->h);
    SDL_FreeSurface( surface );

    return ret;
}

TextSprite *TextRenderer::drawSlow(Fonts font, const std::string& text)
{
    SDL_Surface *surface;
    if(font >= FONT_NULL)
        return NULL;

    SDL_Color white = {255,255,255,255};
    surface = TTF_RenderText_Blended(mFonts[font], text.c_str(), white);
    if(surface == NULL)
    {
        printf("Cannot render text\n");
        return NULL;
    }

    SDL_Texture *t = SDL_CreateTextureFromSurface(sEngine->getRenderer(), 
        surface ); 

    TextSprite *ret = new TextSprite(t, surface->w, surface->h);
    SDL_FreeSurface( surface );

    return ret;

} /* Boiler2D */

}
