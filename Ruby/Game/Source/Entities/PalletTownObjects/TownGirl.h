#pragma once

#include "Entities/Entity.h"

class AnimatedSprite;
class AStarPathFinder;
class ResourceManager;
class TileMap;

class TownGirl : public Entity
{
public:
	TownGirl(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~TownGirl() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
	void Move(SpriteDirection dir, float deltatime);
	void Pause();
	void Resume();
	void SetStop(bool StopNPC);
	void ResetPathFinder() const;
	bool GetNextPath(ivec2 anIndex);
	SpriteDirection CalculateNextInput(ivec2 anIndex);
	void OnEvent(Event* anEvent) override;
	int RangeRandomIntAlg(int min, int max) override;

	[[nodiscard]] bool CheckForCollision(Vector2Float NPCNewPosition) const;
	int* GetInputSet() override;
	bool GetNodeIsClearOnSpecial(int tx, int ty) override;
	int GetMyMapWidth() override;
	int GetMaxPathSize() override;

private:
	std::string AnimationKeys[NUM_DIRECTIONS];
	int m_MyInputSet[MAXPATHSIZE_TOWN_NPC];
	AnimatedSprite* m_Animations[NUM_DIRECTIONS];
	Vector2Float NewPosition;
	ivec2 m_MyNewDestination;
	ivec2 m_MyIndex;
	TileMap* m_MyTileMap;
	ResourceManager* myResourceManager;
	int* m_MyPath;
	int m_CurrentInput;
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	bool m_Stop;
	bool m_IsFirstInput;
	bool m_PathingComplete;
};