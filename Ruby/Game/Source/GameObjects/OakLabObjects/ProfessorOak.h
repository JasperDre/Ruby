#pragma once
class GameObject;
class AnimatedSprite;
class AStarPathFinder;
class ResourceManager;
class TileMap;

class ProfessorOak : public GameObject
{
protected:


public:
	ProfessorOak(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~ProfessorOak();

	virtual void Update(float deltatime) override;
	virtual void PathingUpdate(float delatime);
	virtual void WalkingUpdate(float deltatime);

	virtual void Draw(vec2 camPos, vec2 projecScale) override;

	void SetAIController(AStarPathFinder* aController) { ; }
	void Move(SpriteDirection dir, float deltatime);

	void Pause();
	void Resume();

	void ResetPathFinder();
	bool GetNextPath(ivec2 anIndex);
	SpriteDirection CalculateNextInput(ivec2 anIndex);

	AI_States GetMyState() override;
	virtual void SetMyState(AI_States aState) override;

	virtual bool GetNodeIsClearOnSpecial(int tx, int ty) override;

	void OnEvent(Event* anEvent);

	bool CheckForCollision(vec2 NPCNewPosition);

	virtual int* GetInputSet() override;
	virtual void SetInputSet(int* aPath) override;
	virtual int GetCurrentInput() override;
	virtual void SetCurrentInput(int aCurrentInput) override;
	virtual int GetNextTileFromSet(int aCurrentInput) override;
	virtual void ResetInputSet() override;

	virtual void NPCSeekStartPath() override;

	virtual ivec2 GetMyMinIndex() override;
	virtual ivec2 GetMyMaxIndex() override;

	virtual int GetMyMapWidth() override;
	virtual int GetMaxPathSize() override;

	virtual void SetMyDirection(SpriteDirection aDirection) override;

	virtual int RangeRandomIntAlg(int min, int max) override;

private:
	string AnimationKeys[NUM_DIRECTIONS] = { "OakWalkDown_", "OakWalkRight_", "OakWalkLeft_", "OakWalkUp_" };
	AnimatedSprite* m_Animations[NUM_DIRECTIONS];
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	ResourceManager* myResourceManager;
	TileMap* m_MyTileMap;
	vec2 NewPosition;

	AI_States m_MyState;

	bool m_PathingComplete;
	bool m_IsFirstInput;

	ivec2 m_MyNewDestination;
	ivec2 m_MyIndex;

	int m_CurrentInput;
	int* m_MyPath;
	int m_MyInputSet[OAKMAXPATHSIZE];

};