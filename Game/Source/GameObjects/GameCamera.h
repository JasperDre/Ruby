#pragma once

class Entity;
class Trainer;

class GameCamera : public Entity
{
public:
	GameCamera(GameCore* pGame, Mesh* pMesh, GLuint myTexture, Trainer* myTrainer);
	~GameCamera() override;

	// Inherited via Entity
	void Update(float deltatime) override;

	void Draw();

	void ClampToPlayer(vec2 aPlayerPos);

	vec2 GetCameraPosition();

	void SetMyProjection(vec2 aProjection);
	vec2 GetCameraProjection() const;

	void OnEvent(Event* anEvent);

	void SetScreenSize(vec2 awidowsize);

private:
	Mesh* m_MyMesh;
	vec2 m_MyProjection;
	vec2 m_MyScreenSize;
	vec2 CAMERAMAX;
	vec2 CAMERAMIN;
	vec2 newCamPos;
	vec2 CamOffset;
	bool m_InTransition;
};