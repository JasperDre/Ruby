#pragma once

#include "Event.h"

class DoorEvent : public Event
{
public:
	DoorEvent(int aDoorType)
	{
		DoorType = aDoorType;
	}

	EventTypes GetEventType() const override { return EventType_Door; }
	int GetDoorType() const { return DoorType; }

protected:
	vec2 ColliderPosition;
	int DoorType;
};