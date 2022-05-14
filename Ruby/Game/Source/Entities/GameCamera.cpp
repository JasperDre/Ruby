#include "GamePCH.h"
#include "GameCamera.h"

#include "Game/Game.h"
#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "GameplayHelpers/SceneManager.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"

GameCamera::GameCamera(GameCore* pGame, Mesh* pMesh, GLuint myTexture, Player* aPlayer)
	: Entity(pGame, pMesh, myTexture)
{
	myPosition = Vector2Float(aPlayer->GetPosition() + Vector2Float(0.0f, 1.0f));
	m_MyScreenSize = Vector2Float(static_cast<float>(pGame->GetFramework()->GetWindowWidth()), static_cast<float>(pGame->GetFramework()->GetWindowHeight()));

	CAMERAMIN = Vector2Float(15.0f, 15.0f);
	CAMERAMAX = Vector2Float(48.0f, 48.0f);

	m_InTransition = false;
	newCamPos = Vector2Float(0.0f, 0.0f);
}

void GameCamera::ClampToPlayer(Vector2Float aPlayerPos)
{
	if (m_InTransition)
	{
		const Vector2Float Target = myGameCore->GetSceneManager()->GetActiveScene()->GetPlayerStart() + CamOffset;

		const SpriteDirection aDirection = myGameCore->GetMyPlayer()->GetMyDirection();

		if (aDirection == SpriteDirection::SpriteWalkDown)
		{
			if (Target.myY > aPlayerPos.myY)
			{
				m_InTransition = false;
			}
		}
		else if (aDirection == SpriteDirection::SpriteWalkUp)
		{
			if (Target.myY < aPlayerPos.myY)
			{
				m_InTransition = false;
			}
		}
		else if (aDirection == SpriteDirection::SpriteWalkLeft)
		{
			if (Target.myX > aPlayerPos.myX)
			{
				m_InTransition = false;
			}
		}
		else if (aDirection == SpriteDirection::SpriteWalkRight)
		{
			if (Target.myX < aPlayerPos.myX)
			{
				m_InTransition = false;
			}
		}

	}
	if (m_InTransition == false)
	{
		if (aPlayerPos.myX < CAMERAMAX.myX)
		{
			if (aPlayerPos.myX > CAMERAMIN.myX)
			{
				myPosition.myX = aPlayerPos.myX;
			}
		}
		if (aPlayerPos.myY < CAMERAMAX.myY)
		{
			if (aPlayerPos.myY > CAMERAMIN.myY)
			{
				myPosition.myY = aPlayerPos.myY;
			}
		}
	}
}

Vector2Float GameCamera::GetCameraPosition() const
{
	Vector2Float pos = myPosition;

	pos.myX -= std::fmod(pos.myX, (m_MyScreenSize.myX / 150.0f) / m_MyScreenSize.myX);
	pos.myY -= std::fmod(pos.myY, (m_MyScreenSize.myY / 150.0f) / m_MyScreenSize.myY);

	return pos;
}

void GameCamera::SetMyProjection(Vector2Float aProjection)
{
	m_MyProjection = aProjection;
}

Vector2Float GameCamera::GetCameraProjection() const
{
	return m_MyProjection;
}

void GameCamera::OnEvent(Event* anEvent)
{
	const DoorEvent* doorEvent = dynamic_cast<DoorEvent*>(anEvent);
	if (doorEvent->GetEventType() == EventTypes::EventType_Door)
	{
		const Areas newArea = myGameCore->GetSceneManager()->GetActiveScene()->GetMyArea();
		if (newArea == Areas::Area_OakLab)
		{
			CAMERAMIN = Vector2Float(-6.0f, -6.0f);
			CAMERAMAX = Vector2Float(32.0f, 32.0f);
		}
		if (newArea == Areas::Area_PalletTown)
		{
			CAMERAMIN = Vector2Float(15.0f, 15.0f);
			CAMERAMAX = Vector2Float(48.0f, 48.0f);
		}
		if (newArea == Areas::Area_Woods)
		{
			CAMERAMIN = Vector2Float(16.0f, 18.0f);
			CAMERAMAX = Vector2Float(76.0f, 80.0f);
		}
		if (doorEvent->GetDoorType() != 11 && doorEvent->GetDoorType() != 10)
		{
			const Vector2Float newpos = myGameCore->GetSceneManager()->GetActiveScene()->GetPlayerStart();

			const Vector2Float aDirection = DIRECTIONVECTOR[static_cast<int>(myGameCore->GetMyPlayer()->GetMyDirection())];

			CamOffset = aDirection * (CAMERAMIN);

			newCamPos = newpos + CamOffset;

			SetPosition(newCamPos);

			m_InTransition = true;
		}
	}
}

void GameCamera::SetScreenSize(Vector2Float aSize)
{
	m_MyScreenSize = aSize;
}
