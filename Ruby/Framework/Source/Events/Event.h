#pragma once

enum class EventTypes
{
	EventType_Input,
	EventType_Collision,
	EventType_Door
};

class Event
{
public:
	[[nodiscard]] virtual EventTypes GetEventType() const = 0;
};