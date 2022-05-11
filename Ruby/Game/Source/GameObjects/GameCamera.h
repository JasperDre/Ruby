#pragma once

#include "Entity.h"

class Trainer;

class GameCamera : public Entity
{
public:
	GameCamera(GameCore* pGame, Mesh* pMesh, GLuint myTexture, Trainer* myTrainer);
	~GameCamera() override ;

	// Inherited via Entity
	void Update(float deltatime) override;

	void Draw();

	void ClampToPlayer(Vector2Float aPlayerPos);

	Vector2Float GetCameraPosition();

	void SetMyProjection(Vector2Float aProjection);
	Vector2Float GetCameraProjection();

	void OnEvent(Event* anEvent) override;

	void SetScreenSize(Vector2Float awidowsize);

private:
	Mesh* m_MyMesh;
	Vector2Float m_MyProjection;
	Vector2Float m_MyScreenSize;
	Vector2Float CAMERAMAX;
	Vector2Float CAMERAMIN;
	Vector2Float newCamPos;
	Vector2Float CamOffset;
	bool m_InTransition;
};