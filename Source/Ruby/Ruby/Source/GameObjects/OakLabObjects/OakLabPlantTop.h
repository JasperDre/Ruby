#pragma once
class GameObject;
class Mesh;
class ResourceManager;
class TileMap;

using namespace std;

class OakLabPlantTop : public GameObject
{
public:
	OakLabPlantTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture);
	~OakLabPlantTop();

	virtual void Update(float deltatime) override;

	virtual void Draw(vec2 camPos, vec2 camProject) override;

private:
	const unsigned short OakLabPlantMap[2]{ 2, 3 };

	const unsigned short OakLabPlant_NumTiles = 2;

	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;

	vector<Frame>m_MyFrames;

	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;

	vec2 OaklabPlantPosition;

};