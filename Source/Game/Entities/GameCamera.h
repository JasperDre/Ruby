#pragma once

#include "Entity.h"

class Player;
class GameCore;
class Mesh;
class Vector2Float;

class GameCamera : public Entity
{
public:
	GameCamera(GameCore* pGame, Mesh* pMesh, GLuint myTexture, Player* aPlayer);
	~GameCamera() override = default;

	void Update(float deltatime) override {}
	void OnEvent(Event* anEvent) override;
	void ClampToPlayer(Vector2Float aPlayerPos);

	void SetMyProjection(Vector2Float aProjection);
	void SetScreenSize(Vector2Float aSize);

	[[nodiscard]] Vector2Float GetCameraPosition() const;
	[[nodiscard]] Vector2Float GetCameraProjection() const;

private:
	Vector2Float m_MyProjection;
	Vector2Float m_MyScreenSize;
	Vector2Float CAMERAMAX;
	Vector2Float CAMERAMIN;
	Vector2Float newCamPos;
	Vector2Float CamOffset;
	bool m_InTransition;
};