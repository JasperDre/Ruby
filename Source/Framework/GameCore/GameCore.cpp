#include "GameCore.h"

#include "Events/EventManager.h"

GameCore::GameCore(Framework* aFramework, EventManager* anEventManager)
    : myFramework(aFramework)
    , myEventManager(anEventManager)
{}

GameCore::~GameCore()
{
    delete myEventManager;
}
