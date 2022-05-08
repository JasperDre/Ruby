#pragma once

#include "GameObjects/GameObject.h"

class AStarPathFinder;
class ResourceManager;
class TileMap;

class WildPokemonTile : public GameObject
{
public:
	WildPokemonTile(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~WildPokemonTile() override;

	void Update(float deltatime) override;
	virtual void PathingUpdate(float delatime);
	virtual void WalkingUpdate(float deltatime);
	virtual void TrackToPlayerUpdate(float deltatime);

	void Draw(vec2 camPos, vec2 projecScale) override;

	void SetAIController(AStarPathFinder* aController) { ; }
	void Move(SpriteDirection dir, float deltatime);

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

	virtual void SetMaxIndex(int anIndex) { m_MyMaxIndex = anIndex; }
	virtual void SetMinIndex(int anIndex) { m_MyMinIndex = anIndex; }

	void SetMyDirection(SpriteDirection aDirection) override;
	int RangeRandomIntAlg(int min, int max) override;

private:
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	ResourceManager* myResourceManager;
	vec2 NewPosition;
	ivec2 m_MyNewDestination;
	ivec2 m_MyIndex;
	TileMap* m_MyTileMap;
	int m_MyInputSet[MAXPATHSIZE_TOWN_NPC];
	int* m_MyPath;
	int m_CurrentInput;
	bool m_IsFirstInput;
	bool m_PathingComplete;
	AI_States m_MyState;
};