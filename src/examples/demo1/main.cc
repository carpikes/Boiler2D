#include <Boiler2D/Engine.h>
#include "Screen/MenuScreen.h"

using namespace Boiler2D;

int main()
{
    srand(time(NULL));
    sEngine->setScreen(new MenuScreen, true);
    sEngine->run(); 
    return 0;
}
