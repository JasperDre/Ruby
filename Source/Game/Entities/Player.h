#pragma once

#include "Entity.h"

#include <array>

class AnimatedSprite;
class PlayerController;
class ResourceManager;

class Player : public Entity
{
public:
	Player(ResourceManager* aResourceManager, GameCore* aGameCore, Mesh* aMesh, GLuint aTexture);
	~Player() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
	void OnEvent(Event* anEvent) override;
	void SetPlayerController(PlayerController* aController) { myController = aController; }
	void Move(SpriteDirection dir, float deltatime);
	void Pause() const;
	void Resume() const;
	void SetStop(bool aStopPlayer);
	void PlayerTransition();

	[[nodiscard]] SpriteDirection GetMyDirection() const;
	[[nodiscard]] bool CheckForCollision(Vector2Float aPosition) const;

private:
	std::array<std::string, NUM_DIRECTIONS> myAnimationKeys;
	std::array<AnimatedSprite*, NUM_DIRECTIONS> myAnimations;
	Vector2Float myNewPosition;
	Vector2Float myTransitionDestination;
	ResourceManager* myResourceManager;
	PlayerController* myController;
	SpriteDirection myDirection;
	bool myIsInTransition;
	bool myIsStopped;
};