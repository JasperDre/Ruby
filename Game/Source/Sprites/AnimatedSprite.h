#pragma once

#include "GameObjects/Entity.h"
#include "Constants.h"

class GameCore;
class ResourceManager;
class Mesh;

class AnimatedSprite : public Entity
{
public:
	AnimatedSprite(ResourceManager* aResourceManager, GameCore* myGame, Mesh* myMesh, int aTextureIndex, GLuint aTexture);
	~AnimatedSprite() override;

	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 projScale) override;

	void AddFrame(const std::string& newframe);
	void UseFrame(const std::string& aFrame);

	unsigned int GetFrameCount();

	void SetFrameSpeed(float fps);
	float GetFrameSpeed() const;

	void SetFrameIndex(unsigned int aFrameIndex);

	void SetLoop(bool isLooped);
	bool GetLoop() const;

	void Pause();
	void Resume();
	bool IsAnimating() const;

private:
	std::vector<Frame>m_ActiveFrames;
	ResourceManager* m_MyResourceManager;
	Mesh* m_MyMesh;
	vec2 m_UVScale;
	vec2 m_UVOffset;
	float m_FrameSpeed;
	float m_ElapsedTime;
	int m_MyTexutureIndex;
	int m_CurrentFrame;
	bool m_isPaused;
	bool m_isLooped;
};