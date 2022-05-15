#pragma once

#include "Entities/Entity.h"

#include <array>

class AnimatedSprite;
class AStarPathFinder;
class ResourceManager;
class TileMap;

class ProfessorOak : public Entity
{
public:
	ProfessorOak(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture);
	~ProfessorOak() override;

	void Update(float deltatime) override;
	void PathingUpdate(float delatime);
	void WalkingUpdate(float deltatime);
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
	void Move(SpriteDirection dir, float deltatime);
	void Pause() const;
	void Resume() const;
	void ResetPathFinder() const;
	void OnEvent(Event* anEvent) override {}
	void ResetInputSet() override;
	void NPCSeekStartPath() override;

	void SetMyState(AI_States aState) override;
	void SetInputSet(int* aPath) override;
	void SetCurrentInput(int aCurrentInput) override;
	void SetMyDirection(SpriteDirection aDirection) override;

	bool GetNextPath(Vector2Int anIndex);
	SpriteDirection CalculateNextInput(Vector2Int anIndex);
	[[nodiscard]] AI_States GetMyState() const override { return m_MyState; }
	[[nodiscard]] bool GetNodeIsClearOnSpecial(int tx, int ty) const override;
	[[nodiscard]] bool CheckForCollision(Vector2Float NPCNewPosition) const;
	[[nodiscard]] int* GetInputSet() const override { return m_MyPath; }
	[[nodiscard]] int GetCurrentInput() const override { return m_CurrentInput; }
	[[nodiscard]] int GetNextTileFromSet(int aCurrentInput) const override { return m_MyInputSet[aCurrentInput]; }
	[[nodiscard]] Vector2Int GetMyMinIndex() const override;
	[[nodiscard]] Vector2Int GetMyMaxIndex() const override;
	[[nodiscard]] int GetMyMapWidth() const override;
	[[nodiscard]] int GetMaxPathSize() const override;

private:
	std::array<std::string, NUM_DIRECTIONS> AnimationKeys;
	std::array<int, OAKMAXPATHSIZE> m_MyInputSet;
	std::array<AnimatedSprite*, NUM_DIRECTIONS> m_Animations;
	Vector2Float NewPosition;
	Vector2Int m_MyNewDestination;
	Vector2Int m_MyIndex;
	TileMap* m_MyTileMap;
	int* m_MyPath;
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	AI_States m_MyState;
	int m_CurrentInput;
	bool m_PathingComplete;
	bool m_IsFirstInput;
};