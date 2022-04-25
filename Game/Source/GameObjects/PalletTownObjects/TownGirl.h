#pragma once

class Entity;
class AnimatedSprite;
class AStarPathFinder;
class ResourceManager;
class TileMap;

class TownGirl : public Entity
{
protected:


public:
	TownGirl(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~TownGirl();

	virtual void Update(float deltatime) override;

	virtual void Draw(vec2 camPos, vec2 projecScale) override;

	void SetAIController(AStarPathFinder* aController) { ; }
	void Move(SpriteDirection dir, float deltatime);

	void Pause();
	void Resume();
	void SetStop(bool StopNPC);

	void ResetPathFinder();
	bool GetNextPath(ivec2 anIndex);
	SpriteDirection CalculateNextInput(ivec2 anIndex);

	void OnEvent(Event* anEvent);

	bool CheckForCollision(vec2 NPCNewPosition);

	virtual int* GetInputSet() override;
	virtual bool GetNodeIsClearOnSpecial(int tx, int ty) override;

	virtual int GetMyMapWidth() override;
	virtual int GetMaxPathSize() override;

	virtual int RangeRandomIntAlg(int min, int max) override;

private:
	std::string AnimationKeys[NUM_DIRECTIONS] = { "TownGirlWalkDown_", "TownGirlWalkRight_", "TownGirlWalkLeft_", "TownGirlWalkUp_" };
	AnimatedSprite* m_Animations[NUM_DIRECTIONS];
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	ResourceManager* myResourceManager;
	TileMap* m_MyTileMap;
	vec2 NewPosition;

	bool m_Stop;
	bool m_IsFirstInput;

	ivec2 m_MyNewDestination;
	ivec2 m_MyIndex;
	bool m_PathingComplete;

	int m_CurrentInput;
	int* m_MyPath;
	int m_MyInputSet[MAXPATHSIZE_TOWN_NPC];

};