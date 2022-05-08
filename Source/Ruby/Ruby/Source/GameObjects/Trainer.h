#pragma once
class GameObject;
class AnimatedSprite;
class PlayerController;
class ResourceManager;

class Trainer : public GameObject
{
protected:

	PlayerController* myController;

public:
	Trainer(ResourceManager* aResourceManager, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~Trainer();

	virtual void Update(float deltatime) override;
	virtual void Draw(vec2 camPos, vec2 projecScale) override;

	void SetPlayerController(PlayerController* aController) { myController = aController; }
	void Move(SpriteDirection dir, float deltatime);

	void Pause();
	void Resume();
	void SetStop(bool StopPlayer);

	void OnEvent(Event* anEvent);

	void PlayerTransition();

	SpriteDirection GetMyDirection();

	bool CheckForCollision(vec2 playersNewPosition);

private:

	string AnimationKeys[NUM_DIRECTIONS] = { "PlayerWalkDown_", "PlayerWalkRight_", "PlayerWalkLeft_", "PlayerWalkUp_" };
	AnimatedSprite* m_Animations[NUM_DIRECTIONS];
	SpriteDirection myDirection;
	ResourceManager* myResourceManager;
	vec2 NewPosition;
	vec2 aTransitionDestination;
	bool m_Stop;
	bool m_InTransition;
	int PlayerOriginIndex;

};