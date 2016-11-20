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
    { SPRITE_WARRIOR1,  SHEET_WARRIOR, 0x31,    0,   8,    50 },
    { SPRITE_WARRIOR2,  SHEET_WARRIOR, 0x31,    8,   8,    50 },
    { SPRITE_WARRIOR3,  SHEET_WARRIOR, 0x31,   16,   8,    50 },
    { SPRITE_WARRIOR4,  SHEET_WARRIOR, 0x31,   24,   8,    50 },
    { SPRITE_WARRIOR5,  SHEET_WARRIOR, 0x31,   32,   8,    50 },
    { SPRITE_WARRIOR6,  SHEET_WARRIOR, 0x31,   40,   8,    50 },
    { SPRITE_WARRIOR7,  SHEET_WARRIOR, 0x31,   48,   8,    50 },
    { SPRITE_WARRIOR8,  SHEET_WARRIOR, 0x31,   56,   8,    50 },
    { SPRITE_LAVA0,     SHEET_LAVA,    0x01,    4,   1,     0 },
    { SPRITE_LAVA1,     SHEET_LAVA,    0x01,   10,   1,     0 },
    { SPRITE_LAVA2,     SHEET_LAVA,    0x01,   12,   1,     0 },
    { SPRITE_LAVA3,     SHEET_LAVA,    0x01,   11,   1,     0 },
    { SPRITE_LAVA4,     SHEET_LAVA,    0x01,   20,   1,     0 },
    { SPRITE_LAVA5,     SHEET_LAVA,    0x01,   15,   1,     0 },
    { SPRITE_LAVA6,     SHEET_LAVA,    0x01,    9,   1,     0 },//!
    { SPRITE_LAVA7,     SHEET_LAVA,    0x01,    7,   1,     0 },
    { SPRITE_LAVA8,     SHEET_LAVA,    0x01,   22,   1,     0 },
    { SPRITE_LAVA9,     SHEET_LAVA,    0x01,   14,   1,     0 },//!
    { SPRITE_LAVA10,    SHEET_LAVA,    0x01,   17,   1,     0 },
    { SPRITE_LAVA11,    SHEET_LAVA,    0x01,    6,   1,     0 },
    { SPRITE_LAVA12,    SHEET_LAVA,    0x01,   21,   1,     0 },
    { SPRITE_LAVA13,    SHEET_LAVA,    0x01,    2,   1,     0 },
    { SPRITE_LAVA14,    SHEET_LAVA,    0x01,    1,   1,     0 },
    { SPRITE_LAVA15,    SHEET_LAVA,    0x01,   16,   1,     0 },
    { SPRITE_LAVA_ANIM1,SHEET_LAVA,    0x01,   25,   1,     0 },
    { SPRITE_LAVA_ANIM2,SHEET_LAVA,    0x01,   26,   1,     0 },
    { SPRITE_LAVA_ANIM3,SHEET_LAVA,    0x01,   27,   1,     0 },

    { SPRITE_DIRT0,     SHEET_DIRT,    0x01,    4,   1,     0 },
    { SPRITE_DIRT1,     SHEET_DIRT,    0x01,   10,   1,     0 },
    { SPRITE_DIRT2,     SHEET_DIRT,    0x01,   12,   1,     0 },
    { SPRITE_DIRT3,     SHEET_DIRT,    0x01,   11,   1,     0 },
    { SPRITE_DIRT4,     SHEET_DIRT,    0x01,   20,   1,     0 },
    { SPRITE_DIRT5,     SHEET_DIRT,    0x01,   15,   1,     0 },
    { SPRITE_DIRT6,     SHEET_DIRT,    0x01,    9,   1,     0 },//!
    { SPRITE_DIRT7,     SHEET_DIRT,    0x01,    7,   1,     0 },
    { SPRITE_DIRT8,     SHEET_DIRT,    0x01,   22,   1,     0 },
    { SPRITE_DIRT9,     SHEET_DIRT,    0x01,   14,   1,     0 },//!
    { SPRITE_DIRT10,    SHEET_DIRT,    0x01,   17,   1,     0 },
    { SPRITE_DIRT11,    SHEET_DIRT,    0x01,    6,   1,     0 },
    { SPRITE_DIRT12,    SHEET_DIRT,    0x01,   21,   1,     0 },
    { SPRITE_DIRT13,    SHEET_DIRT,    0x01,    2,   1,     0 },
    { SPRITE_DIRT14,    SHEET_DIRT,    0x01,    1,   1,     0 },
    { SPRITE_DIRT15,    SHEET_DIRT,    0x01,   16,   1,     0 },
    // altre
    // ...
    { SPRITE_NULL,      SHEET_NULL,     0x00,    0,   0,     0 }
};

const sheetinfo_t the_sheets[] = {
    { SHEET_ISO,  "data/iso.png",        64,     64  },
    { SHEET_FIRE, "data/fire.png",       64,    128  },
    { SHEET_WARRIOR, "data/warrior.png", 48,     48 },
    { SHEET_LAVA, "/tmp/lpc_terrain/twosided/lava.png", 32,     32 },
    { SHEET_DIRT, "/tmp/lpc_terrain/twosided/dirt2.png", 32,     32 },
    { SHEET_NULL, "", 0, 0},
};

const fontsinfo_t the_fonts[] = {
//    ID,            NAME,            SIZE
    { FONT_BSHERWOOD, "data/SHERWOOD.TTF",   80 },
    { FONT_SSHERWOOD, "data/SHERWOOD.TTF",   30 },
    { FONT_NULL,      "",                0 },
};

