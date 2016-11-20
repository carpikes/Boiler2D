#include <Boiler2D/Engine.h>
#include "Game/World.h"
#include "Game/MapFactory.h"
#include "Game/Map.h"
#include <unistd.h>

int main()
{
    World w;
    printf("Hello World\n");

    while(w.update(0.02)) 
        usleep(20000);
    return 0;
}
