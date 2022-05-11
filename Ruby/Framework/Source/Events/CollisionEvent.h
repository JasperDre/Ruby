#pragma once

#include "Event.h"

class CollisionEvent : public Event
{
public:
	CollisionEvent()
		: myColliderPosition(0.0f)
		, myObsticlePosition(0.0f)
	{}

	CollisionEvent(Vector2Float anObsticlePos, Vector2Float aColliderPos)
		: myColliderPosition(aColliderPos)
		, myObsticlePosition(anObsticlePos)
	{}

	[[nodiscard]] EventTypes GetEventType() const override { return EventTypes::EventType_Collision; }
	[[nodiscard]] Vector2Float GetColliderPosition() const { return myColliderPosition; }
	[[nodiscard]] Vector2Float GetObsticlePosition() const { return myObsticlePosition; }

protected:
	Vector2Float myColliderPosition;
	Vector2Float myObsticlePosition;
};