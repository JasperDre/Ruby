#pragma once
#include "GameObjects/GameObject.h"
#include "Constants.h"

class GameCore;
class ResourceManager;
class Mesh;

class AnimatedSprite : public GameObject
{
public:
	AnimatedSprite(ResourceManager* aResourceManager, GameCore* myGame, Mesh* myMesh, int aTextureIndex, GLuint aTexture);
	~AnimatedSprite();

	void Update(float deltatime);
	void Draw(vec2 camPos, vec2 projScale);

	void AddFrame(const std::string& newframe);	
	void UseFrame(const std::string& aFrame);

	unsigned int GetFrameCount();

	void SetFrameSpeed(float fps);
	float GetFrameSpeed();

	void SetFrameIndex(unsigned int aFrameIndex);

	void SetLoop(bool isLooped);
	bool GetLoop();

	void Pause();
	void Resume();
	bool IsAnimating();

private:

	std::vector<Frame>m_ActiveFrames;
	float m_FrameSpeed;
	float m_ElapsedTime;
	vec2 m_UVScale;
	vec2 m_UVOffset;
	int m_CurrentFrame;
	bool m_isLooped;
	bool m_isPaused;
	ResourceManager* m_MyResourceManager;
	Mesh* m_MyMesh;
	int m_MyTexutureIndex;
};

