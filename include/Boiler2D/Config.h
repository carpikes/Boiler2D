#ifndef BOILER2D_CONFIG_H
#define BOILER2D_CONFIG_H

#include "Common.h"

#define SCREEN_WIDTH     1024
#define SCREEN_HEIGHT    768

// Elencare qua i font TTF 
enum Fonts {
    FONT_BSHERWOOD,
    FONT_SSHERWOOD,
    //...
    FONT_NULL // ultimo!
};

// Elencare qua i nomi interni degli sprite sheets
enum SpriteSheets {
    SHEET_ISO,
    SHEET_FIRE,
    SHEET_NULL   // ultimo!
};

// in SpriteList non mettere "= NUMERO", vengono allocati N interi dove N e` il
// numero di id (quindi un = 0xffff farebbe allocare tanta memoria!)
// Indicare qua i nomi interni delle sprites
enum SpriteList {
    SPRITE_BLACK,
    SPRITE_REDWALL1, 
    SPRITE_REDWALL2, 
    SPRITE_REDWALL3, 
    SPRITE_REDWALL4, 
    SPRITE_REDWALL5, 
    SPRITE_REDWALL6, 
    SPRITE_REDWALL7, 
    SPRITE_REDWALL8, 
    SPRITE_REDWALL9, 
    SPRITE_REDWALL10,
    SPRITE_REDWALL11,
    SPRITE_REDWALL12,
    SPRITE_REDWALL13,
    SPRITE_REDWALL14,
    SPRITE_REDWALL15,
    SPRITE_REDWALL16,
    SPRITE_PAVY,
    SPRITE_PAVB,
    SPRITE_PAVA,
    SPRITE_PAVG,
    SPRITE_HUMAN,
    SPRITE_ENEMY,
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

#endif /* ifndef BOILER2D_CONFIG_H */
