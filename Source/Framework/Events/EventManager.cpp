#include "FrameworkPCH.h"

EventManager::~EventManager()
{
    while (!myEvents.empty())
    {
        delete myEvents.front();
        myEvents.pop();
    }
}

void EventManager::QueueEvent(Event* anEvent)
{
    assert(anEvent);
    myEvents.push(anEvent);
}

void EventManager::DispatchEvents(GameCore* aGameCore)
{
    while (!myEvents.empty())
    {
        Event* pEvent = myEvents.front();
        aGameCore->OnEvent(pEvent);
        myEvents.pop();
        assert(pEvent);
        delete pEvent;
    }
}