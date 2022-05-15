#pragma once

#include "Event.h"

class DoorEvent : public Event
{
public:
	DoorEvent()
		: myColliderPosition(0.0f)
		, myDoorType(0)
	{}

	DoorEvent(int aDoorType)
		: myColliderPosition(0.0f)
		, myDoorType(aDoorType)
	{}

	[[nodiscard]] EventTypes GetEventType() const override { return EventTypes::EventType_Door; }
	[[nodiscard]] int GetDoorType() const { return myDoorType; }

protected:
	Vector2Float myColliderPosition;
	int myDoorType;
};