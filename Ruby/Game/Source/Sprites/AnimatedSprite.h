#pragma once

#include "Entities/Entity.h"
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
	void Draw(Vector2Float camPos, Vector2Float projScale) override;

	void AddFrame(const std::string& newframe);
	void UseFrame(const std::string& aFrame);

	[[nodiscard]] unsigned int GetFrameCount() const;

	void SetFrameSpeed(float fps);
	[[nodiscard]] float GetFrameSpeed() const;

	void SetFrameIndex(unsigned int aFrameIndex);

	void SetLoop(bool isLooped);
	[[nodiscard]] bool GetLoop() const;

	void Pause();
	void Resume();
	[[nodiscard]] bool IsAnimating() const;

private:
	std::vector<Frame> m_ActiveFrames;
	Vector2Float m_UVScale;
	Vector2Float m_UVOffset;
	ResourceManager* m_MyResourceManager;
	Mesh* m_MyMesh;
	float m_FrameSpeed;
	float m_ElapsedTime;
	int m_CurrentFrame;
	int m_MyTexutureIndex;
	bool m_isPaused;
	bool m_isLooped;
};