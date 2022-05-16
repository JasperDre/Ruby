#pragma once

#include "Entity.h"

class Player;
class GameCore;
class Mesh;
class Vector2Float;

class GameCamera : public Entity
{
public:
	GameCamera(GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier, Player* aPlayer);
	~GameCamera() override = default;

	void Update(float deltatime) override {}
	void OnEvent(Event* anEvent) override;
	void ClampToPlayer(Vector2Float aPlayerPos);

	void SetMyProjection(Vector2Float aProjection);
	void SetScreenSize(Vector2Float aSize);

	[[nodiscard]] Vector2Float GetCameraPosition() const;
	[[nodiscard]] Vector2Float GetCameraProjection() const;

private:
	Vector2Float myProjection;
	Vector2Float myScreenSize;
	Vector2Float myCameraMax;
	Vector2Float myCameraMin;
	Vector2Float myNewCamPosition;
	Vector2Float myCameraOffset;
	bool myIsInTransition;
};