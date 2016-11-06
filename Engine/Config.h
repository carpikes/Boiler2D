#ifndef MICROGUE_CONFIG_H
#define MICROGUE_CONFIG_H

#include "Common.h"

#define SCREEN_WIDTH     1280
#define SCREEN_HEIGHT    720

// Elencare qua i font TTF 
enum Fonts {
    FONT_BSHERWOOD,
    FONT_SSHERWOOD,
    //...
    FONT_NULL // ultimo!
};

// Elencare qua i nomi interni degli sprite sheets
enum SpriteSheets {
    SHEET_DEMO,
    SHEET_FIRE,
    SHEET_NULL   // ultimo!
};

// in SpriteList non mettere "= NUMERO", vengono allocati N interi dove N e` il
// numero di id (quindi un = 0xffff farebbe allocare tanta memoria!)
// Indicare qua i nomi interni delle sprites
enum SpriteList {
    SPRITE_GRASS,
    SPRITE_WALL,
    SPRITE_PLANT,
    SPRITE_FIRE,
    // altre sprites
    // ...
    
    // lasciare sprite_null per ultima
    SPRITE_NULL // la uso per tenere il conto di quante sono
};

enum SpriteFlags {
    SPRITEFLAG_VALID        = 0x01,
    SPRITEFLAG_WALL         = 0x02,
    SPRITEFLAG_ENEMY        = 0x04,
    SPRITEFLAG_COLLECTABLE  = 0x08,

    SPRITEFLAG_ANIMATED     = 0x10,
    SPRITEFLAG_REPEAT       = 0x20,
};

struct fontsinfo_t {
    Fonts id;
    std::string file;
    int size;
};

struct sheetinfo_t {
    SpriteSheets id;
    std::string file;
    int tilew;
    int tileh;
};

struct spriteinfo_t {
    SpriteList id;
    SpriteSheets sheet;
    int flags;
    int n;
    int count;
    uint32_t time;
};

extern const spriteinfo_t the_sprites[];
extern const sheetinfo_t the_sheets[];
extern const fontsinfo_t the_fonts[];

#endif /* ifndef MICROGUE_CONFIG_H */
