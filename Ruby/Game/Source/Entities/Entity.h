#pragma once

class Mesh;
class AStarPathFinder;
class GameCore;
enum class AI_States;

class Entity
{
public:
	Entity(GameCore* pGame, Mesh* pMesh, unsigned int aTextureIdentifier);
	virtual ~Entity() = default;

	virtual void OnEvent(Event* pEvent) {}
	virtual void Update(float deltatime) {}
	virtual void Draw(Vector2Float camPos, Vector2Float projScale);

	virtual bool IsColliding(Entity* pOtherGameObject) { return false; }
	virtual void OnCollision(Entity* pOtherGameObject) {}

	virtual AI_States GetMyState();
	virtual void SetMyState(AI_States aState) {}

	virtual bool GetNodeIsClearOnSpecial(int tx, int ty) { return false; }
	virtual int RangeRandomIntAlg(int min, int max) { return 0; }

	virtual int* GetInputSet() { return nullptr; }
	virtual void SetInputSet(int* aPath) {}

	virtual int GetCurrentInput() { return 0; }
	virtual void SetCurrentInput(int aCurrentInput) {}

	virtual int GetNextTileFromSet(int aCurrentInput) { return 0; }

	virtual void NPCSeekStartPath() {}
	virtual void ResetInputSet() {}

	[[nodiscard]] Vector2Float GetPosition() const { return m_Position; }
	[[nodiscard]] ivec2 GetMyIndex() const { return ivec2(static_cast<int>(m_Position.myX / TILESIZE), static_cast<int>(m_Position.myY / TILESIZE)); }
	[[nodiscard]] float GetAngle() const { return m_Angle; }
	[[nodiscard]] float GetRadius() const { return m_Radius; }
	virtual ivec2 GetMyMinIndex() { return ivec2(); }
	virtual ivec2 GetMyMaxIndex() { return ivec2(); }
	virtual int GetMyNodeOffset() { return m_MyMinIndex; }
	virtual AStarPathFinder* GetPathFinder() { if (m_MyPathFinder) { return m_MyPathFinder; } else { return nullptr; } }
	virtual int GetMyMapWidth() { return 0; }
	virtual int GetMaxPathSize() { return 0; }

	void SetPosition(Vector2Float pos) { m_Position = pos; }
	void SetAngle(float angle) { m_Angle = angle; }
	void SetRadius(float radius) { m_Radius = radius; }
	virtual void SetMyDirection(SpriteDirection aDirection) {}

protected:
	Vector2Float m_Position;
	Vector2Float my_UVOffset;
	unsigned int myTextureIdentifier;
	GameCore* m_pGame;
	Mesh* m_pMesh;
	AStarPathFinder* m_MyPathFinder;
	float m_Angle;
	float m_Radius;
	int m_MyMinIndex;
	int m_MyMaxIndex;
};
