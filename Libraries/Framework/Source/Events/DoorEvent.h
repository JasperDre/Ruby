#pragma once
#ifndef _DoorEvent_H_
#define _DoorEvent_H_

class DoorEvent : public Event
{
protected:
	vec2 ColliderPosition;
	int DoorType;

public:
	DoorEvent(int aDoorType)
	{
		DoorType = aDoorType;
	}

	EventTypes GetEventType() { return EventType_Door; }
	int GetDoorType() { return DoorType; }

};
#endif // _DoorEvent_H_