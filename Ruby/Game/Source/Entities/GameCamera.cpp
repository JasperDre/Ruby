#include "GamePCH.h"
#include "GameCamera.h"

#include "Game/Game.h"
#include "Entities/Entity.h"
#include "Entities/Trainer.h"
#include "GameplayHelpers/SceneManager.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"

GameCamera::GameCamera(GameCore* pGame, Mesh* pMesh, GLuint myTexture, Trainer* myTrainer) : Entity(pGame, pMesh, myTexture)
{
	m_MyMesh = pMesh;
	m_Position = Vector2Float(myTrainer->GetPosition() + Vector2Float(0.0f, 1.0f));
	m_MyScreenSize = Vector2Float(pGame->GetFramework()->GetWindowWidth(), pGame->GetFramework()->GetWindowHeight());

	CAMERAMIN = Vector2Float(15.0f, 15.0f);
	CAMERAMAX = Vector2Float(48.0f, 48.0f);

	m_InTransition = false;
	newCamPos = Vector2Float(0.0f, 0.0f);
}

GameCamera::~GameCamera()
{

}

void GameCamera::Update(float deltatime)
{

}

void GameCamera::Draw()
{

}

void GameCamera::ClampToPlayer(Vector2Float aPlayerPos)
{
	if (m_InTransition)
	{
		Vector2Float Target = m_pGame->GetSceneManager()->GetActiveScene()->GetPlayerStart() + CamOffset;

		SpriteDirection aDirection = m_pGame->GetMyPlayer()->GetMyDirection();

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
				m_Position.myX = aPlayerPos.myX;
			}
		}
		if (aPlayerPos.myY < CAMERAMAX.myY)
		{
			if (aPlayerPos.myY > CAMERAMIN.myY)
			{
				m_Position.myY = aPlayerPos.myY;
			}
		}
	}
}

Vector2Float GameCamera::GetCameraPosition()
{
	Vector2Float pos = m_Position;

	pos.myX -= fmod(pos.myX, (m_MyScreenSize.myX/150) / m_MyScreenSize.myX);
	pos.myY -= fmod(pos.myY, (m_MyScreenSize.myY/150) / m_MyScreenSize.myY);

	return pos;
}

void GameCamera::SetMyProjection(Vector2Float aProjection)
{
	m_MyProjection = aProjection;
}

Vector2Float GameCamera::GetCameraProjection()
{
	return m_MyProjection;
}

void GameCamera::OnEvent(Event * anEvent)
{
	DoorEvent* e = (DoorEvent*)anEvent;
	if (e->GetEventType() == EventTypes::EventType_Door)
	{
		Areas newArea = m_pGame->GetSceneManager()->GetActiveScene()->GetMyArea();
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
		if (e->GetDoorType() != 11 && e->GetDoorType() != 10)
		{
			Vector2Float newpos = m_pGame->GetSceneManager()->GetActiveScene()->GetPlayerStart();

			Vector2Float aDirection = DIRECTIONVECTOR[static_cast<int>(m_pGame->GetMyPlayer()->GetMyDirection())];

			CamOffset = aDirection * (CAMERAMIN);

			newCamPos = newpos + CamOffset;

			SetPosition(newCamPos);

			m_InTransition = true;
		}
	}
}

void GameCamera::SetScreenSize(Vector2Float awindowsize)
{
	m_MyScreenSize = awindowsize;
}
