#pragma once

class Mesh;
class Event;
class AStarPathFinder;
class GameCore;
class Vector2Float;
enum class AI_States;

class Entity
{
public:
	Entity(GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	virtual ~Entity() = default;

	virtual void OnEvent(Event* pEvent) {}
	virtual void Update(float deltatime) {}
	virtual void Draw(Vector2Float camPos, Vector2Float projScale);
	virtual void OnCollision(Entity* pOtherGameObject) {}
	virtual void NPCSeekStartPath() {}
	virtual void ResetInputSet() {}

	virtual void SetInputSet(int* aPath) {}
	virtual void SetCurrentInput(int aCurrentInput) {}
	virtual void SetMyState(AI_States aState) {}
	virtual void SetMyDirection(SpriteDirection aDirection) {}
	void SetPosition(Vector2Float pos) { myPosition = pos; }
	void SetAngle(float angle) { myAngle = angle; }
	void SetRadius(float radius) { myRadius = radius; }

	[[nodiscard]] virtual bool IsColliding(Entity* pOtherGameObject) const { return false; }
	[[nodiscard]] virtual AI_States GetMyState() const;
	[[nodiscard]] virtual bool GetNodeIsClearOnSpecial(int tx, int ty) const { return false; }
	[[nodiscard]] virtual int RangeRandomIntAlg(int min, int max) const { return 0; }
	[[nodiscard]] virtual int* GetInputSet() const { return nullptr; }
	[[nodiscard]] virtual int GetCurrentInput() const { return 0; }
	[[nodiscard]] virtual int GetNextTileFromSet(int aCurrentInput) const { return 0; }
	[[nodiscard]] Vector2Float GetPosition() const { return myPosition; }
	[[nodiscard]] ivec2 GetMyIndex() const;
	[[nodiscard]] float GetAngle() const { return myAngle; }
	[[nodiscard]] float GetRadius() const { return myRadius; }
	[[nodiscard]] virtual ivec2 GetMyMinIndex() const { return ivec2(); }
	[[nodiscard]] virtual ivec2 GetMyMaxIndex() const { return ivec2(); }
	[[nodiscard]] virtual int GetMyNodeOffset() const { return myMinIndex; }
	[[nodiscard]] virtual AStarPathFinder* GetPathFinder() const { return myPathFinder; }
	[[nodiscard]] virtual int GetMyMapWidth() const { return 0; }
	[[nodiscard]] virtual int GetMaxPathSize() const { return 0; }

protected:
	Vector2Float myPosition;
	Vector2Float myUVOffset;
	GameCore* myGameCore;
	Mesh* myMesh;
	AStarPathFinder* myPathFinder;
	unsigned int myTextureIdentifier;
	float myAngle;
	float myRadius;
	int myMinIndex;
	int myMaxIndex;
};
