#pragma once
class GameObject;
class Mesh;
class ResourceManager;
class TileMap;

using namespace std;

class OakLabTableTop : public GameObject
{
public:
	OakLabTableTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture);
	~OakLabTableTop();

	virtual void Update(float deltatime) override;

	virtual void Draw(vec2 camPos, vec2 camProject) override;

private:
	const unsigned short OakLabTableTopMap[3] = { 3, 4, 5 };

	const unsigned short OakLabTableTop_NumTiles = 3;

	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
	vector<Frame> m_MyFrames;

	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;

	vec2 OakLabTableTopPosition;

};