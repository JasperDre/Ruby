#pragma once

#include "GameObjects/GameObject.h"

class AnimatedSprite;
class AStarPathFinder;
class ResourceManager;
class TileMap;

class ProfessorOak : public GameObject
{
public:
	ProfessorOak(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~ProfessorOak() override;

	void Update(float deltatime) override;
	void PathingUpdate(float delatime);
	void WalkingUpdate(float deltatime);

	void Draw(vec2 camPos, vec2 projecScale) override;

	void SetAIController(AStarPathFinder* aController) {}
	void Move(SpriteDirection dir, float deltatime);

	void Pause();
	void Resume();

	void ResetPathFinder();
	bool GetNextPath(ivec2 anIndex);
	SpriteDirection CalculateNextInput(ivec2 anIndex);

	AI_States GetMyState() override;
	void SetMyState(AI_States aState) override;

	bool GetNodeIsClearOnSpecial(int tx, int ty) override;

	void OnEvent(Event* anEvent) override;

	bool CheckForCollision(vec2 NPCNewPosition);

	int* GetInputSet() override;
	void SetInputSet(int* aPath) override;
	int GetCurrentInput() override;
	void SetCurrentInput(int aCurrentInput) override;
	int GetNextTileFromSet(int aCurrentInput) override;
	void ResetInputSet() override;

	void NPCSeekStartPath() override;

	ivec2 GetMyMinIndex() override;
	ivec2 GetMyMaxIndex() override;

	int GetMyMapWidth() override;
	int GetMaxPathSize() override;

	void SetMyDirection(SpriteDirection aDirection) override;

	int RangeRandomIntAlg(int min, int max) override;

private:
	std::string AnimationKeys[NUM_DIRECTIONS] = { "OakWalkDown_", "OakWalkRight_", "OakWalkLeft_", "OakWalkUp_" };
	int m_MyInputSet[OAKMAXPATHSIZE];
	vec2 NewPosition;
	ivec2 m_MyNewDestination;
	ivec2 m_MyIndex;
	AnimatedSprite* m_Animations[NUM_DIRECTIONS];
	TileMap* m_MyTileMap;
	ResourceManager* myResourceManager;
	int* m_MyPath;
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	AI_States m_MyState;
	int m_CurrentInput;
	bool m_PathingComplete;
	bool m_IsFirstInput;
};