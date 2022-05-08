#pragma once

#include "Event.h"

class CollisionEvent : public Event
{
public:
	CollisionEvent()
		: myColliderPosition(0.0f)
		, myObsticlePosition(0.0f)
	{}

	CollisionEvent(vec2 anObsticlePos, vec2 aColliderPos)
		: myColliderPosition(aColliderPos)
		, myObsticlePosition(anObsticlePos)
	{}

	[[nodiscard]] EventTypes GetEventType() const override { return EventTypes::EventType_Collision; }
	[[nodiscard]] vec2 GetColliderPosition() const { return myColliderPosition; }
	[[nodiscard]] vec2 GetObsticlePosition() const { return myObsticlePosition; }

protected:
	vec2 myColliderPosition;
	vec2 myObsticlePosition;
};