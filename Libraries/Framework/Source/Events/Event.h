#pragma once

enum EventTypes
{
	EventType_Input,
	EventType_Collision,
	EventType_Door
};

class Event
{
public:
	virtual ~Event() {}

	virtual EventTypes GetEventType() const = 0;
};