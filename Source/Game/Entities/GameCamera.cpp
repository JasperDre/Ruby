#include "GamePCH.h"
#include "GameCamera.h"

#include "Game/Game.h"
#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "GameplayHelpers/SceneManager.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"

GameCamera::GameCamera(GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier, Player* aPlayer)
	: Entity(aGameCore, aMesh, aTextureIdentifier)
{
	myPosition = Vector2Float(aPlayer->GetPosition() + Vector2Float(0.0f, 1.0f));
	myScreenSize = Vector2Float(static_cast<float>(aGameCore->GetFramework()->GetWindowWidth()), static_cast<float>(aGameCore->GetFramework()->GetWindowHeight()));

	myCameraMin = Vector2Float(15.0f, 15.0f);
	myCameraMax = Vector2Float(48.0f, 48.0f);

	myIsInTransition = false;
	myNewCamPosition = Vector2Float(0.0f, 0.0f);
}

void GameCamera::ClampToPlayer(Vector2Float aPlayerPos)
{
	if (myIsInTransition)
	{
		const Vector2Float Target = myGameCore->GetSceneManager()->GetActiveScene()->GetPlayerStart() + myCameraOffset;

		const SpriteDirection aDirection = myGameCore->GetMyPlayer()->GetMyDirection();

		if (aDirection == SpriteDirection::SpriteWalkDown)
		{
			if (Target.myY > aPlayerPos.myY)
			{
				myIsInTransition = false;
			}
		}
		else if (aDirection == SpriteDirection::SpriteWalkUp)
		{
			if (Target.myY < aPlayerPos.myY)
			{
				myIsInTransition = false;
			}
		}
		else if (aDirection == SpriteDirection::SpriteWalkLeft)
		{
			if (Target.myX > aPlayerPos.myX)
			{
				myIsInTransition = false;
			}
		}
		else if (aDirection == SpriteDirection::SpriteWalkRight)
		{
			if (Target.myX < aPlayerPos.myX)
			{
				myIsInTransition = false;
			}
		}

	}
	if (myIsInTransition == false)
	{
		if (aPlayerPos.myX < myCameraMax.myX)
		{
			if (aPlayerPos.myX > myCameraMin.myX)
			{
				myPosition.myX = aPlayerPos.myX;
			}
		}
		if (aPlayerPos.myY < myCameraMax.myY)
		{
			if (aPlayerPos.myY > myCameraMin.myY)
			{
				myPosition.myY = aPlayerPos.myY;
			}
		}
	}
}

Vector2Float GameCamera::GetCameraPosition() const
{
	Vector2Float pos = myPosition;

	pos.myX -= std::fmod(pos.myX, (myScreenSize.myX / 150.0f) / myScreenSize.myX);
	pos.myY -= std::fmod(pos.myY, (myScreenSize.myY / 150.0f) / myScreenSize.myY);

	return pos;
}

void GameCamera::SetMyProjection(Vector2Float aProjection)
{
	myProjection = aProjection;
}

Vector2Float GameCamera::GetCameraProjection() const
{
	return myProjection;
}

void GameCamera::OnEvent(Event* anEvent)
{
	const DoorEvent* doorEvent = dynamic_cast<DoorEvent*>(anEvent);
	if (doorEvent->GetEventType() == EventTypes::EventType_Door)
	{
		const Areas newArea = myGameCore->GetSceneManager()->GetActiveScene()->GetMyArea();
		if (newArea == Areas::Area_OakLab)
		{
			myCameraMin = Vector2Float(-6.0f, -6.0f);
			myCameraMax = Vector2Float(32.0f, 32.0f);
		}
		if (newArea == Areas::Area_PalletTown)
		{
			myCameraMin = Vector2Float(15.0f, 15.0f);
			myCameraMax = Vector2Float(48.0f, 48.0f);
		}
		if (newArea == Areas::Area_Woods)
		{
			myCameraMin = Vector2Float(16.0f, 18.0f);
			myCameraMax = Vector2Float(76.0f, 80.0f);
		}
		if (doorEvent->GetDoorType() != 11 && doorEvent->GetDoorType() != 10)
		{
			const Vector2Float newpos = myGameCore->GetSceneManager()->GetActiveScene()->GetPlayerStart();

			const Vector2Float aDirection = DIRECTIONVECTOR[static_cast<int>(myGameCore->GetMyPlayer()->GetMyDirection())];

			myCameraOffset = aDirection * (myCameraMin);

			myNewCamPosition = newpos + myCameraOffset;

			SetPosition(myNewCamPosition);

			myIsInTransition = true;
		}
	}
}

void GameCamera::SetScreenSize(Vector2Float aSize)
{
	myScreenSize = aSize;
}
