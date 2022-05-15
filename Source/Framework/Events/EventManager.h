#pragma once

#include <queue>

class GameCore;
class Event;

class EventManager
{
public:
    virtual ~EventManager();

    virtual void QueueEvent(Event* anEvent);
    virtual void DispatchEvents(GameCore* aGameCore);

protected:
    std::queue<Event*> myEvents;
};