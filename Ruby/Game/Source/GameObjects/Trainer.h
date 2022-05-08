#pragma once

#include "GameObject.h"

class AnimatedSprite;
class PlayerController;
class ResourceManager;

class Trainer : public GameObject
{
public:
	Trainer(ResourceManager* aResourceManager, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~Trainer() override;

	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 projecScale) override;

	void SetPlayerController(PlayerController* aController) { myController = aController; }
	void Move(SpriteDirection dir, float deltatime);

	void Pause();
	void Resume();
	void SetStop(bool StopPlayer);

	void OnEvent(Event* anEvent) override;

	void PlayerTransition();

	SpriteDirection GetMyDirection();

	bool CheckForCollision(vec2 playersNewPosition);

protected:
	PlayerController* myController;

private:
	std::string AnimationKeys[NUM_DIRECTIONS] = { "PlayerWalkDown_", "PlayerWalkRight_", "PlayerWalkLeft_", "PlayerWalkUp_" };
	AnimatedSprite* m_Animations[NUM_DIRECTIONS];
	vec2 NewPosition;
	vec2 aTransitionDestination;
	ResourceManager* myResourceManager;
	SpriteDirection myDirection;
	int PlayerOriginIndex;
	bool m_InTransition;
	bool m_Stop;
};