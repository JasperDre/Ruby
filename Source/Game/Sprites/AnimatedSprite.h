#pragma once

#include <string>
#include <vector>

#include "Entities/Entity.h"
#include "GameplayHelpers/Frame.h"

class GameCore;
class ResourceManager;
class Mesh;

class AnimatedSprite : public Entity
{
public:
	AnimatedSprite(ResourceManager* aResourceManager, GameCore* aGameCore, Mesh* aMesh, int aTextureIndex, unsigned int aTextureIdentifier);
	~AnimatedSprite() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float projScale) override;
	void AddFrame(const std::string& newframe);
	void UseFrame(const std::string& aFrame);
	void Pause();
	void Resume();

	void SetFrameSpeed(float fps);
	void SetFrameIndex(unsigned int aFrameIndex);
	void SetLoop(bool isLooped);

	[[nodiscard]] unsigned int GetFrameCount() const;
	[[nodiscard]] float GetFrameSpeed() const;
	[[nodiscard]] bool GetLoop() const;
	[[nodiscard]] bool IsAnimating() const;

private:
	std::vector<Frame> myActiveFrames;
	Vector2Float mUVScale;
	ResourceManager* myResourceManager;
	float myFrameSpeed;
	float myElapsedTime;
	unsigned int myCurrentFrame;
	int myTextureIndex;
	bool myIsPaused;
	bool myIsLooped;
};