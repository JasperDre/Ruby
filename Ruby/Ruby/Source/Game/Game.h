#ifndef __Game_H__
#define __Game_H__


class Mesh;
class GameObject;

class ResourceManager;
class TileMap;
class TileMapPalletTown;
class TileMapOakLab;
class TileMapExtras;
class Trainer;
class UIObject;
class PlayerController;
class GameCamera;

class SceneManager;

class Game : public GameCore
{
public:
    static const int Game_WORLD_SIZE_X = 50;
    static const int Game_WORLD_SIZE_Y = 50;

protected:
    ShaderProgram* m_pShader;
	ShaderProgram* m_pDebugShader;

	Mesh* m_TrainerMesh;
	Mesh* m_TileMesh;
	Mesh* m_CameraMesh;
	Mesh* m_UIMesh;

	ResourceManager* m_MyResourceManager;
	TileMap* m_PalletTileMap;
	TileMap* m_OakLabTileMap;
	TileMap* m_WoodsTileMap;
	TileMap* m_ExtrasTileMap;

	Trainer* m_Trainer;
	UIObject* m_UICanvas;
	GameCamera* m_TrainerCamera;
    PlayerController* m_pPlayerController;

	SceneManager* m_MySceneManager;

	GLuint m_Tileset;
	GLuint m_OakLabTileset;
	GLuint m_Sprites;
	GLuint m_WoodsTileset;
	GLuint m_ExtrasSet;
	GLuint m_BattleScene;

	vec2 aWindowSize;

public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltatime);
    virtual void Draw();

	virtual TileMap* GetTileMap() override;
	virtual SceneManager* GetSceneManager() override;
	virtual ShaderProgram* GetShader() override;
	virtual ShaderProgram* GetDebugShader() override;
	virtual Trainer* GetMyPlayer() override;

	void SetCameraScreenSize(float width, float height);

    void CheckForCollisions();
};

#endif //__Game_H__
