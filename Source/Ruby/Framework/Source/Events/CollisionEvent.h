#ifndef _CollisionEvent_H_
#define _CollisionEvent_H_

class CollisionEvent : public Event
{
protected:
	vec2 ColliderPosition;
	vec2 ObsticlePosition;

public:
	CollisionEvent(vec2 anObsticlePos, vec2 aColliderPos)
	{
		ColliderPosition = aColliderPos;
		ObsticlePosition = anObsticlePos;
	}

	EventTypes GetEventType() { return EventType_Collision; }
	vec2 GetColliderPosition() { return ColliderPosition; }
	vec2 GetObsticlePosition() { return ObsticlePosition; }

};
#endif // _CollisionEvent_H_