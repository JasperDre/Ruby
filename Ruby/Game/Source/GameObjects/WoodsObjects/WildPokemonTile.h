#pragma once

#include "GameObjects/Entity.h"

class AStarPathFinder;
class ResourceManager;
class TileMap;

class WildPokemonTile : public Entity
{
public:
	WildPokemonTile(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~WildPokemonTile() override;

	void Update(float deltatime) override;
	virtual void PathingUpdate(float delatime);
	virtual void WalkingUpdate(float deltatime);
	virtual void TrackToPlayerUpdate(float deltatime);

	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
	void Move(SpriteDirection dir, float deltatime);

	void ResetPathFinder();
	bool GetNextPath(ivec2 anIndex);
	SpriteDirection CalculateNextInput(ivec2 anIndex);

	AI_States GetMyState() override;
	void SetMyState(AI_States aState) override;

	bool GetNodeIsClearOnSpecial(int tx, int ty) override;

	void OnEvent(Event* anEvent) override;

	[[nodiscard]] bool CheckForCollision(Vector2Float NPCNewPosition) const;

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
	int m_MyInputSet[MAXPATHSIZE_TOWN_NPC];
	ResourceManager* myResourceManager;
	Vector2Float NewPosition;
	ivec2 m_MyNewDestination;
	ivec2 m_MyIndex;
	TileMap* m_MyTileMap;
	int* m_MyPath;
	int m_CurrentInput;
	bool m_IsFirstInput;
	bool m_PathingComplete;
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	AI_States m_MyState;
};