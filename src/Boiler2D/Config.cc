#include <Boiler2D/Config.h>

// Qua van definite le sprites
const spriteinfo_t the_sprites[] = {
//    NOME_SPRITE,      NOME_SHEET,    FLAGS,    N, CNT,   DELAY (anim)
    { SPRITE_BLACK,     SHEET_ISO,     0x01,    0,   1,     0 },
    { SPRITE_REDWALL1,  SHEET_ISO,     0x03,    1,   1,     0 },
    { SPRITE_REDWALL2,  SHEET_ISO,     0x03,    2,   1,     0 },
    { SPRITE_REDWALL3,  SHEET_ISO,     0x03,    3,   1,     0 },
    { SPRITE_REDWALL4,  SHEET_ISO,     0x03,    4,   1,     0 },
    { SPRITE_REDWALL5,  SHEET_ISO,     0x03,    5,   1,     0 },
    { SPRITE_REDWALL6,  SHEET_ISO,     0x03,    6,   1,     0 },
    { SPRITE_REDWALL7,  SHEET_ISO,     0x03,    7,   1,     0 },
    { SPRITE_REDWALL8,  SHEET_ISO,     0x03,    8,   1,     0 },
    { SPRITE_REDWALL9,  SHEET_ISO,     0x03,    9,   1,     0 },
    { SPRITE_REDWALL10, SHEET_ISO,     0x03,    10,  1,     0 },
    { SPRITE_REDWALL11, SHEET_ISO,     0x03,    11,  1,     0 },
    { SPRITE_REDWALL12, SHEET_ISO,     0x03,    12,  1,     0 },
    { SPRITE_REDWALL13, SHEET_ISO,     0x03,    13,  1,     0 },
    { SPRITE_REDWALL14, SHEET_ISO,     0x03,    14,  1,     0 },
    { SPRITE_REDWALL15, SHEET_ISO,     0x03,    15,  1,     0 },
    { SPRITE_REDWALL16, SHEET_ISO,     0x03,    16,  1,     0 },
    { SPRITE_PAVY,      SHEET_ISO,     0x01,    71,  1,     0 },
    { SPRITE_PAVB,      SHEET_ISO,     0x01,    72,  1,     0 },
    { SPRITE_PAVA,      SHEET_ISO,     0x01,    73,  1,     0 },
    { SPRITE_PAVG,      SHEET_ISO,     0x01,    74,  1,     0 },
    { SPRITE_HUMAN,     SHEET_ISO,     0x01,   160,  1,     0 },
    { SPRITE_ENEMY,     SHEET_ISO,     0x01,   161,  1,     0 },
    { SPRITE_FIRE,      SHEET_FIRE,    0x31,    0,  32,    20 },
    // altre
    // ...
    { SPRITE_NULL,      SHEET_NULL,     0x00,    0,   0,     0 }
};

const sheetinfo_t the_sheets[] = {
    { SHEET_ISO,  "data/iso.png",        64,     64  },
    { SHEET_FIRE, "data/fire.png",       64,     128 },
    { SHEET_NULL, "", 0, 0},
};

const fontsinfo_t the_fonts[] = {
//    ID,            NAME,            SIZE
    { FONT_BSHERWOOD, "data/SHERWOOD.TTF",  100 },
    { FONT_SSHERWOOD, "data/SHERWOOD.TTF",   40 },
    { FONT_NULL,      "",                0 },
};

