#ifndef BOILER2D_SPRITE_MANAGER_H
#define BOILER2D_SPRITE_MANAGER_H

#include "Common.h"
#include "Config.h"
#include "Sprite.h"

class SpriteManager 
{
public:
    static SpriteManager *instance()
    { 
        static SpriteManager g; 
        return &g; 
    }

    ~SpriteManager()
    {
        for(Sprite *i : mSprites)
            if(i != NULL)
                delete i;
        for(Image *i : mSheets)
            if(i != NULL)
                delete i;
    }

    void load(int id)
    {
        if(id >= (int)mSprites.size())
        {
            printf("trying to load sprite %d, too high\n", id);
            return;
        }

        spriteinfo_t s = mSpritesInfo[id];
        if(mSprites[id] != NULL) // e` gia` caricata
            return; 

        if(s.sheet >= SHEET_NULL) 
        {
            printf("invalid sheet for sprite %d\n", id);
            return;
        }

        Image *img = mSheets[s.sheet];
        mSprites[id] = new ImageSprite(img, s);
    }

    void load(int id_from, int id_to)
    {
        if(id_to > (int)mSprites.size())
            id_to = mSprites.size() - 1;

        for(int i=id_from; i<=id_to; i++)
            load(i);
    }

    // carica al volo se non precaricata
    ImageSprite* get(int id) 
    {
        if(id >= (int)mSprites.size()) 
        {
            printf("sprite %d too high\n", id);
            return NULL;
        }

        ImageSprite *ret = mSprites[id];
        if(ret == NULL) 
        {
            load(id);
            ret = mSprites[id];
        }
        return ret;
    }
private:
    std::vector<Image*> mSheets;
    std::vector<ImageSprite*> mSprites;
    std::vector<spriteinfo_t> mSpritesInfo;

    SpriteManager()
    {
        const int sz = SPRITE_NULL;
        const int shsz = SHEET_NULL;

        mSheets.resize(shsz, NULL);
        mSprites.resize(sz, NULL);
        mSpritesInfo.resize(sz);

        for(int i=0;i<shsz; i++)
        {
            int id = the_sheets[i].id;
            assert(id < sz);
            mSheets[id] = new Image(id, the_sheets[i]);
        }

        for(int i=0;i<sz; i++)
        {
            int id = the_sprites[i].id;
            assert(id < sz);
            mSpritesInfo[id] = the_sprites[i];
        }
    }
};

#define sSpriteManager SpriteManager::instance()


#endif /* ifndef BOILER2D_SPRITE_MANAGER_H */
