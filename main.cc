#include "Common.h"
#include "Engine.h"
#include "Screen/MenuScreen.h"

int main()
{
    sEngine->setScreen(new MenuScreen, true);
    sEngine->run(); 
    return 0;
}
