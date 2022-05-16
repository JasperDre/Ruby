#include "GamePCH.h"
#include "AnimatedSprite.h"

#include "GameplayHelpers/ResourceManager.h"
#include "Mesh/Mesh.h"

AnimatedSprite::AnimatedSprite(ResourceManager* aResourceManager, GameCore* aGameCore, Mesh* aMesh, int aTextureIndex, unsigned int aTextureIdentifier)
	: Entity(aGameCore, aMesh, aTextureIdentifier)
	, myFrameSpeed(0)
	, myIsPaused(false)
	, myIsLooped(false)
{
	myTextureIdentifier = aTextureIdentifier;
	myResourceManager = aResourceManager;
	myCurrentFrame = 0;
	myElapsedTime = 0.0f;
	myTextureIndex = aTextureIndex;
}

AnimatedSprite::~AnimatedSprite()
{
	myResourceManager = nullptr;
	myMesh = nullptr;
	myGameCore = nullptr;
}

void AnimatedSprite::Update(float deltatime)
{
	if (!myIsPaused)
	{
		myElapsedTime += deltatime;

		const unsigned int lastFrame = myCurrentFrame;

		unsigned int frameIndex = static_cast<unsigned int>((myElapsedTime / (1.0 / myFrameSpeed)));

		if (myIsLooped)
			frameIndex = frameIndex % myActiveFrames.size();

		if (frameIndex != lastFrame)
			SetFrameIndex(frameIndex);
	}

	// Safety check
	if (myCurrentFrame > 3)
	{
		myCurrentFrame = 0;
	}

	const Vector2Float frameorigin = myActiveFrames.at(myCurrentFrame).myOrigin;
	const Vector2Float framesize = myActiveFrames.at(myCurrentFrame).mySize;
	mUVScale = Vector2Float((framesize.myX / myResourceManager->GetTextureSize(myTextureIndex).x), (framesize.myY / myResourceManager->GetTextureSize(myTextureIndex).y));
	myUVOffset = Vector2Float((frameorigin.myX / myResourceManager->GetTextureSize(myTextureIndex).x), (frameorigin.myY / myResourceManager->GetTextureSize(myTextureIndex).y));
}

void AnimatedSprite::Draw(Vector2Float camPos, Vector2Float projScale)
{
	myMesh->Draw(myPosition, myAngle, Vector2Float((TILESIZE / 10.0f) * 5.5f, (TILESIZE / 10.0f) * 11.0f), camPos, projScale, myTextureIdentifier, mUVScale, myUVOffset);
}

void AnimatedSprite::AddFrame(const std::string& newframe)
{
	myActiveFrames.push_back(myResourceManager->GetFrameAtIndex(newframe));
}

void AnimatedSprite::UseFrame(const std::string& aFrame)
{
	myActiveFrames.clear();
	myActiveFrames.push_back(myResourceManager->GetFrameAtIndex(aFrame));
}

unsigned int AnimatedSprite::GetFrameCount() const
{
	return static_cast<unsigned int>(myActiveFrames.size());
}

void AnimatedSprite::SetFrameSpeed(float fps)
{
	myFrameSpeed = fps;
}

float AnimatedSprite::GetFrameSpeed() const
{
	return myFrameSpeed;
}

void AnimatedSprite::SetFrameIndex(unsigned int aFrameIndex)
{
	if (aFrameIndex < myActiveFrames.size())
		myCurrentFrame = aFrameIndex;
}

void AnimatedSprite::SetLoop(bool isLooped)
{
	myIsLooped = isLooped;
}

bool AnimatedSprite::GetLoop() const
{
	return myIsLooped;
}

void AnimatedSprite::Pause()
{
	myIsPaused = true;
}

void AnimatedSprite::Resume()
{
	myIsPaused = false;
}

bool AnimatedSprite::IsAnimating() const
{
	return myIsPaused;
}
