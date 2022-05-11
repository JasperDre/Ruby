#pragma once

#include "Entity.h"

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

	void SetPlayerController(PlayerController* aController) { myController = aController; }
	void Move(SpriteDirection dir, float deltatime);

	void Pause();
	void Resume() const;
	void SetStop(bool StopPlayer);

	void OnEvent(Event* anEvent) override;

	void PlayerTransition();

	[[nodiscard]] SpriteDirection GetMyDirection() const;

	[[nodiscard]] bool CheckForCollision(Vector2Float aPosition) const;

protected:
	PlayerController* myController;

private:
	std::string AnimationKeys[NUM_DIRECTIONS];
	AnimatedSprite* m_Animations[NUM_DIRECTIONS];
	Vector2Float NewPosition;
	Vector2Float aTransitionDestination;
	ResourceManager* myResourceManager;
	SpriteDirection myDirection;
	bool m_InTransition;
	bool m_Stop;
};