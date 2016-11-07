#ifndef BOILER2D_IMAGE_H
#define BOILER2D_IMAGE_H

#include "Common.h"
#include "Config.h"

class Image 
{
public:
    Image(int id, const sheetinfo_t& info) : mId(id), mInfo(info)
    {
        mUsageCount = 0;
        mTexture = NULL;
        mNRows = 0;
        mNColumns = 0;
    }

    ~Image()
    {
        unload();
    }

    SDL_Texture *getTexture()
    {
        assert(mTexture != NULL);
        return mTexture;
    }

    void incrementUsageCount()
    {
        if(mUsageCount == 0)
            load();

        mUsageCount++;
    }

    void decrementUsageCount()
    {
        mUsageCount--;
        if(mUsageCount < 0)
            printf("Image %d(%s) usage count < 0\n", mId, mInfo.file.c_str());
        if(mUsageCount == 0)
            unload();
    }

    const sheetinfo_t& getInfo() const
    { 
        return mInfo;
    }

    int getNSpritesY() const
    { 
        assert(mNRows != 0); 
        return mNRows;
    }

    int getNSpritesX() const
    { 
        assert(mNColumns != 0);
        return mNColumns;
    }
private:
    const int mId;
    const sheetinfo_t mInfo;

    SDL_Texture *mTexture;
    int mUsageCount, mNColumns, mNRows;

    bool load();
    void unload();
};

#endif /* ifndef BOILER2D_IMAGE_H */
