#include "FrameworkPCH.h"

GameCore::GameCore(Framework* aFramework, EventManager* anEventManager)
    : myFramework(aFramework)
    , myEventManager(anEventManager)
{}

GameCore::~GameCore()
{
    delete myEventManager;
}
