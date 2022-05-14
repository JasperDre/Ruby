#pragma once

#include "Event.h"
#include <InputManager.h>

class InputEvent : public Event
{
public:
    InputEvent(Keys aKey) : myKey(aKey) {}

    [[nodiscard]] EventTypes GetEventType() const override { return EventTypes::EventType_Input; }

    Keys myKey;
};