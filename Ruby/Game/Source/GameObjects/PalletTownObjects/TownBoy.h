#pragma once

#include "GameObjects/GameObject.h"

class AnimatedSprite;
class AStarPathFinder;
class ResourceManager;
class TileMap;

class TownBoy : public GameObject
{
public:
	TownBoy(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~TownBoy() override;

	void Update(float deltatime) override;

	void Draw(vec2 camPos, vec2 projecScale) override;

	void SetAIController(AStarPathFinder* aController) {}
	void Move(SpriteDirection dir, float deltatime);

	void Pause();
	void Resume();
	void SetStop(bool StopNPC);

	void ResetPathFinder();
	bool GetNextPath(ivec2 anIndex);
	SpriteDirection CalculateNextInput(ivec2 anIndex);

	void OnEvent(Event* anEvent) override;

	bool CheckForCollision(vec2 NPCNewPosition);

	int* GetInputSet() override;

	bool GetNodeIsClearOnSpecial(int tx, int ty) override;

	int GetMyMapWidth() override;
	int GetMaxPathSize() override;

	int RangeRandomIntAlg(int min, int max) override;

private:
	std::string AnimationKeys[NUM_DIRECTIONS] = { "TownBoyWalkDown_", "TownBoyWalkRight_", "TownBoyWalkLeft_", "TownBoyWalkUp_" };
	int m_MyInputSet[MAXPATHSIZE_TOWN_NPC];
	AnimatedSprite* m_Animations[NUM_DIRECTIONS];
	vec2 NewPosition;
	ivec2 m_MyNewDestination;
	ivec2 m_MyIndex;
	ResourceManager* myResourceManager;
	TileMap* m_MyTileMap;
	int* m_MyPath;
	SpriteDirection myNewDirection;
	SpriteDirection myDirection;
	int m_CurrentInput;
	bool m_IsFirstInput;
	bool m_PathingComplete;
	bool m_Stop;
};
