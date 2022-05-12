#pragma once

#include "Entity.h"

#include <array>

class AnimatedSprite;
class PlayerController;
class ResourceManager;

class Trainer : public Entity
{
public:
	Trainer(ResourceManager* aResourceManager, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~Trainer() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
	void OnEvent(Event* anEvent) override;
	void SetPlayerController(PlayerController* aController) { myController = aController; }
	void Move(SpriteDirection dir, float deltatime);
	void Pause();
	void Resume() const;
	void SetStop(bool StopPlayer);
	void PlayerTransition();

	[[nodiscard]] SpriteDirection GetMyDirection() const;
	[[nodiscard]] bool CheckForCollision(Vector2Float aPosition) const;

private:
	std::array<std::string, NUM_DIRECTIONS> AnimationKeys;
	std::array<AnimatedSprite*, NUM_DIRECTIONS> m_Animations;
	Vector2Float NewPosition;
	Vector2Float aTransitionDestination;
	ResourceManager* myResourceManager;
	PlayerController* myController;
	SpriteDirection myDirection;
	bool m_InTransition;
	bool m_Stop;
};