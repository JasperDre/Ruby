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

	void SetProjection(Vector2Float aProjection);
	void SetScreenSize(Vector2Float aSize);

	[[nodiscard]] Vector2Float GetCameraPosition() const;
	[[nodiscard]] Vector2Float GetProjection() const { return myProjection; }
	[[nodiscard]] Vector2Float GetScreenSize() const { return myScreenSize; }
	[[nodiscard]] Vector2Float GetMin() const { return myCameraMin; }
	[[nodiscard]] Vector2Float GetMax() const { return myCameraMax; }
	[[nodiscard]] Vector2Float GetOffset() const { return myCameraOffset; }
	[[nodiscard]] bool IsInTransition() const { return myIsInTransition; }

private:
	Vector2Float myProjection;
	Vector2Float myScreenSize;
	Vector2Float myCameraMax;
	Vector2Float myCameraMin;
	Vector2Float myCameraOffset;
	bool myIsInTransition;
};