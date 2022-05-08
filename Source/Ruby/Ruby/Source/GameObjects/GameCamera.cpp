#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "GameCamera.h"

#include "Mesh/Mesh.h"
#include "GameObjects/Trainer.h"

#include "Game/Game.h"

#include "GameplayHelpers/SceneManager.h"
#include "Scenes/Scene.h"

GameCamera::GameCamera(GameCore* pGame, Mesh* pMesh, GLuint myTexture, Trainer* myTrainer) : GameObject(pGame, pMesh, myTexture)
{
	m_MyMesh = pMesh;
	m_Position = vec2(myTrainer->GetPosition() + vec2(0.0f, 1.0f));
	m_MyScreenSize = vec2(pGame->GetFramework()->GetWindowWidth(), pGame->GetFramework()->GetWindowHeight());

	CAMERAMIN = vec2(15.0f, 15.0f);
	CAMERAMAX = vec2(48.0f, 48.0f);

	m_InTransition = false;
	newCamPos = vec2(0.0f, 0.0f);
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

void GameCamera::ClampToPlayer(vec2 aPlayerPos)
{
	if (m_InTransition)
	{
		vec2 Target = m_pGame->GetSceneManager()->GetActiveScene()->GetPlayerStart() + CamOffset;

		SpriteDirection aDirection = m_pGame->GetMyPlayer()->GetMyDirection();

		if (aDirection == SpriteWalkDown)
		{
			if (Target.y > aPlayerPos.y)
			{
				m_InTransition = false;
			}
		}
		else if (aDirection == SpriteWalkUp)
		{
			if (Target.y < aPlayerPos.y)
			{
				m_InTransition = false;
			}
		}
		else if (aDirection == SpriteWalkLeft)
		{
			if (Target.x > aPlayerPos.x)
			{
				m_InTransition = false;
			}
		}
		else if (aDirection == SpriteWalkRight)
		{
			if (Target.x < aPlayerPos.x)
			{
				m_InTransition = false;
			}
		}

	}
	if (m_InTransition == false)
	{
		if (aPlayerPos.x < CAMERAMAX.x)
		{
			if (aPlayerPos.x > CAMERAMIN.x)
			{
				m_Position.x = aPlayerPos.x;
			}
		}
		if (aPlayerPos.y < CAMERAMAX.y)
		{
			if (aPlayerPos.y > CAMERAMIN.y)
			{
				m_Position.y = aPlayerPos.y;
			}
		}
	}
}

vec2 GameCamera::GetCameraPosition()
{
	vec2 pos = m_Position;

	pos.x -= fmod(pos.x, (m_MyScreenSize.x/150) / m_MyScreenSize.x);
	pos.y -= fmod(pos.y, (m_MyScreenSize.y/150) / m_MyScreenSize.y);

	return pos;
}

void GameCamera::SetMyProjection(vec2 aProjection)
{
	m_MyProjection = aProjection;
}

vec2 GameCamera::GetCameraProjection()
{
	return m_MyProjection;
}

void GameCamera::OnEvent(Event * anEvent)
{
	DoorEvent* e = (DoorEvent*)anEvent;
	if (e->GetEventType() == EventType_Door)
	{
		Areas newArea = m_pGame->GetSceneManager()->GetActiveScene()->GetMyArea();
		if (newArea == Area_OakLab)
		{
			CAMERAMIN = vec2(-6.0f, -6.0f);
			CAMERAMAX = vec2(32.0f, 32.0f);
		}
		if (newArea == Area_PalletTown)
		{
			CAMERAMIN = vec2(15.0f, 15.0f);
			CAMERAMAX = vec2(48.0f, 48.0f);
		}
		if (newArea == Area_Woods)
		{
			CAMERAMIN = vec2(16.0f, 18.0f);
			CAMERAMAX = vec2(76.0f, 80.0f);
		}
		if (e->GetDoorType() != 11 && e->GetDoorType() != 10)
		{
			vec2 newpos = m_pGame->GetSceneManager()->GetActiveScene()->GetPlayerStart();

			vec2 aDirection = DIRECTIONVECTOR[m_pGame->GetMyPlayer()->GetMyDirection()];

			CamOffset = aDirection * (CAMERAMIN);

			newCamPos = newpos + CamOffset;

			SetPosition(newCamPos);

			m_InTransition = true;
		}
	}
}

void GameCamera::SetScreenSize(vec2 awindowsize)
{
	m_MyScreenSize = awindowsize;
}
