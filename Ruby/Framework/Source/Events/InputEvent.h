#pragma once

#include "Event.h"
#include <InputManager.h>

class InputEvent : public Event
{
public:
    InputEvent(Keys aKey, bool anIsReleased) : myKey(aKey), myIsReleased(anIsReleased) {}

    [[nodiscard]] EventTypes GetEventType() const override { return EventTypes::EventType_Input; }

    Keys myKey;
    const bool myIsReleased;
};