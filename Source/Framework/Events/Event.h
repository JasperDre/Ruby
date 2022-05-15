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
	virtual ~Event() = default;

	[[nodiscard]] virtual EventTypes GetEventType() const = 0;
};