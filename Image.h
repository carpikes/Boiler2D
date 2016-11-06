#ifndef MICROGUE_IMAGE_H
#define MICROGUE_IMAGE_H

#include "Common.h"
#include "Config.h"

class Image 
{
public:
    Image(int id, const std::string& name) : mId(id), mName(name)
    {
        mUsageCount = 0;
        mTexture = NULL;
    }

    ~Image() {
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
            printf("Image %d(%s) usage count < 0\n", mId, mName.c_str());
        if(mUsageCount == 0)
            unload();
    }
private:
    const int mId;
    const std::string mName;

    SDL_Texture *mTexture;
    int mUsageCount;

    bool load();
    void unload();
};

#endif /* ifndef MICROGUE_IMAGE_H */
