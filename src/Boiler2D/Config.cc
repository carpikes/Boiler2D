#include <Boiler2D/Config.h>

// Qua van definite le sprites
const spriteinfo_t the_sprites[] = {
//    NOME_SPRITE,      NOME_SHEET,    FLAGS,    N, CNT,   DELAY (anim)
//    { SPRITE_GRASS,     SHEET_DEMO,     0x01,    0,   1,     0 },
//    { SPRITE_WALL,      SHEET_DEMO,     0x03,    9*8 + 4,   1,     0 },
//    { SPRITE_PLANT,     SHEET_DEMO,     0x03,   10,   1,     0 },
    { SPRITE_FIRE,      SHEET_FIRE,     0x31,    0,  32,    20 },
    // altre
    // ...
    { SPRITE_NULL,      SHEET_NULL,     0x00,    0,   0,     0 }
};

const sheetinfo_t the_sheets[] = {
//    { SHEET_DEMO, "magecity.png",   32,     32  },
    { SHEET_FIRE, "data/fire.png",       64,     128 },
    { SHEET_NULL, "", 0, 0},
};

const fontsinfo_t the_fonts[] = {
//    ID,            NAME,            SIZE
    { FONT_BSHERWOOD, "data/SHERWOOD.TTF",  100 },
    { FONT_SSHERWOOD, "data/SHERWOOD.TTF",   40 },
    { FONT_NULL,      "",                0 },
};

