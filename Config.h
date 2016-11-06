#ifndef MICROGUE_CONFIG_H
#define MICROGUE_CONFIG_H

#include "Common.h"

#define SCREEN_WIDTH     800
#define SCREEN_HEIGHT    600

// Elencare qua i nomi interni degli sprite sheets
enum SpriteSheets {
    SHEET_DEMO,
    SHEET_NULL
};

// in SpriteList non mettere "= NUMERO", vengono allocati N interi dove N e` il
// numero di id (quindi un = 0xffff farebbe allocare tanta memoria!)
// Indicare qua i nomi interni delle sprites
enum SpriteList {
    SPRITE_DEMO,
    // altre sprites
    // ...
    
    // lasciare sprite_null per ultima
    SPRITE_NULL // la uso per tenere il conto di quante sono
};

enum SpriteFlags {
    SPRITEFLAG_VALID = 1,
};

struct sheetinfo_t {
    SpriteSheets id;
    std::string file;
};

struct spriteinfo_t {
    SpriteList id;
    SpriteSheets sheet;
    int flags;
    int x;
    int y;
    int w;
    int h;
};

// Qua van definite le sprites
const spriteinfo_t the_sprites[] = {
//    NOME_SPRITE, NOME_SHEET, 0x01,    X, Y,   W,   H 
    { SPRITE_DEMO, SHEET_DEMO, 0x01,    0, 0, 128, 128 },
    // altre
    // ...
    { SPRITE_NULL, SHEET_NULL, 0x00,    0, 0, 0, 0 }
};

const sheetinfo_t the_sheets[] = {
    { SHEET_DEMO, "demo.png" },
    { SHEET_NULL, "" },
};


#endif /* ifndef MICROGUE_CONFIG_H */
