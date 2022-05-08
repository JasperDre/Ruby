#pragma once
#pragma once
class GameObject;
class Mesh;
class ResourceManager;
class TileMap;

using namespace std;

class OakLabMachineTop : public GameObject
{
public:
	OakLabMachineTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture);
	~OakLabMachineTop();

	virtual void Update(float deltatime) override;

	virtual void Draw(vec2 camPos, vec2 camProject) override;

private:

	const unsigned short OakLabMachineMap[2]{ 4, 5 };

	const unsigned short OakLabMachine_NumTiles = 2;

	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
	vector<Frame> m_MyFrames;

	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;

	vec2 OaklabMachinePosition;

};