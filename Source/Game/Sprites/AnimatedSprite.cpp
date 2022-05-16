#include "GamePCH.h"
#include "AnimatedSprite.h"

#include "GameplayHelpers/ResourceManager.h"
#include "Mesh/Mesh.h"

AnimatedSprite::AnimatedSprite(ResourceManager* aResourceManager, GameCore* myGame, Mesh * myMesh, int aTextureIndex, GLuint aTexture):Entity(myGame, myMesh, aTexture)
{
	m_MyMesh = myMesh;
	myTextureIdentifier = aTexture;
	m_MyResourceManager = aResourceManager;

	m_CurrentFrame = 0;
	m_ElapsedTime = 0.0f;
	m_MyTexutureIndex = aTextureIndex;
}

AnimatedSprite::~AnimatedSprite()
{
	m_MyResourceManager = nullptr;
	myMesh = nullptr;
	myGameCore = nullptr;
}

void AnimatedSprite::Update(float deltatime)
{
	if (!m_isPaused)
	{
		m_ElapsedTime += deltatime;

		const unsigned int lastFrame = m_CurrentFrame;

		unsigned int frameIndex = static_cast<unsigned int>((m_ElapsedTime / (1.0 / m_FrameSpeed)));

		if (m_isLooped)
			frameIndex = frameIndex % m_ActiveFrames.size();

		if (frameIndex != lastFrame)
			SetFrameIndex(frameIndex);
	}

	// Safety check
	if (m_CurrentFrame > 3)
	{
		m_CurrentFrame = 0;
	}

	const Vector2Float frameorigin = m_ActiveFrames.at(m_CurrentFrame).myOrigin;
	const Vector2Float framesize = m_ActiveFrames.at(m_CurrentFrame).mySize;
	m_UVScale = Vector2Float((framesize.myX / m_MyResourceManager->GetTextureSize(m_MyTexutureIndex).x), (framesize.myY / m_MyResourceManager->GetTextureSize(m_MyTexutureIndex).y));
	m_UVOffset = Vector2Float((frameorigin.myX / m_MyResourceManager->GetTextureSize(m_MyTexutureIndex).x), (frameorigin.myY / m_MyResourceManager->GetTextureSize(m_MyTexutureIndex).y));
}

void AnimatedSprite::Draw(Vector2Float camPos, Vector2Float projScale)
{
	myMesh->Draw(myPosition, myAngle, Vector2Float((TILESIZE / 10.0f) * 5.5f, (TILESIZE / 10.0f) * 11.0f), camPos, projScale, myTextureIdentifier, m_UVScale, m_UVOffset);
}

void AnimatedSprite::AddFrame(const std::string& newframe)
{
	m_ActiveFrames.push_back(m_MyResourceManager->GetFrameAtIndex(newframe));
}

void AnimatedSprite::UseFrame(const std::string& aFrame)
{
	m_ActiveFrames.clear();
	m_ActiveFrames.push_back(m_MyResourceManager->GetFrameAtIndex(aFrame));
}

unsigned int AnimatedSprite::GetFrameCount() const
{
	return static_cast<unsigned int>(m_ActiveFrames.size());
}

void AnimatedSprite::SetFrameSpeed(float fps)
{
	m_FrameSpeed = fps;
}

float AnimatedSprite::GetFrameSpeed() const
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

bool AnimatedSprite::GetLoop() const
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

bool AnimatedSprite::IsAnimating() const
{
	return m_isPaused;
}
