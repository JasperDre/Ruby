#include "GamePCH.h"
#include "AnimatedSprite.h"
#include "GameObjects/GameObject.h"
#include "Mesh/Mesh.h"
#include "GameplayHelpers/ResourceManager.h"
#include <fstream>

AnimatedSprite::AnimatedSprite(ResourceManager* aResourceManager, GameCore* myGame, Mesh * myMesh, int aTextureIndex, GLuint aTexture):GameObject(myGame, myMesh, aTexture)
{
	m_MyMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = aResourceManager;

	m_CurrentFrame = 0;
	m_ElapsedTime = 0.0f;
	m_MyTexutureIndex = aTextureIndex;
}

AnimatedSprite::~AnimatedSprite()
{
	m_MyResourceManager = nullptr;
	m_pMesh = nullptr;
	m_pGame = nullptr;
}

void AnimatedSprite::Update(float deltatime)
{
	if (m_isPaused == false)
	{
		m_ElapsedTime += deltatime;

		int lastFrame = m_CurrentFrame;

		int frameIndex = static_cast<int>((m_ElapsedTime / (1.0 / m_FrameSpeed)));

		if (m_isLooped == true)
		{
			frameIndex = frameIndex % m_ActiveFrames.size();
		}
		if (frameIndex != lastFrame)
		{
			SetFrameIndex(frameIndex);
		}
	}

	//safety check
	if (m_CurrentFrame > 3)
	{
		m_CurrentFrame = 0;
	}

	vec2 frameorigin = m_ActiveFrames.at(m_CurrentFrame).origin;
	vec2 framesize = m_ActiveFrames.at(m_CurrentFrame).size;
	m_UVScale = vec2((framesize.x / m_MyResourceManager->GetTextureSize(m_MyTexutureIndex).x), (framesize.y / m_MyResourceManager->GetTextureSize(m_MyTexutureIndex).y));
	m_UVOffset = vec2((frameorigin.x / m_MyResourceManager->GetTextureSize(m_MyTexutureIndex).x), (frameorigin.y / m_MyResourceManager->GetTextureSize(m_MyTexutureIndex).y));

}

void AnimatedSprite::Draw(vec2 camPos, vec2 projScale)
{
	m_pMesh->Draw(m_Position, m_Angle, vec2((TILESIZE / 10.0f) * 5.5f, (TILESIZE / 10.0f) * 11.0f), camPos, projScale, m_pMyTexture, m_UVScale, m_UVOffset);
}

void AnimatedSprite::AddFrame(const std::string& newframe)
{
	m_ActiveFrames.push_back(m_MyResourceManager->GetFrameat(newframe));
}

void AnimatedSprite::UseFrame(const std::string& aFrame)
{
	//clear the current vector of Frames
	m_ActiveFrames.empty();
	//Insert only the desired frame
	m_ActiveFrames.push_back(m_MyResourceManager->GetFrameat(aFrame));
}

unsigned int AnimatedSprite::GetFrameCount()
{
	return m_ActiveFrames.size();
}

void AnimatedSprite::SetFrameSpeed(float fps)
{
	m_FrameSpeed = fps;
}

float AnimatedSprite::GetFrameSpeed()
{
	return m_FrameSpeed;
}

void AnimatedSprite::SetFrameIndex(unsigned int aFrameIndex)
{
	if (aFrameIndex < m_ActiveFrames.size())
	{
		m_CurrentFrame = aFrameIndex;
	}
}

void AnimatedSprite::SetLoop(bool isLooped)
{
	m_isLooped = isLooped;
}

bool AnimatedSprite::GetLoop()
{
	return m_isLooped;
}

void AnimatedSprite::Pause()
{
	m_isPaused = true;
}

void AnimatedSprite::Resume()
{
	m_isPaused = false;
}

bool AnimatedSprite::IsAnimating()
{
	return m_isPaused;
}
