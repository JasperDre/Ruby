#pragma once
class Mesh;
class TileMap;
class ResourceManager;


class Canvas : public Mesh
{
public:
    Canvas(TileMap* aTileMap, ResourceManager* aResourceManager);
    ~Canvas();

	void GeneratePalletVertexData(const unsigned short BitMap[MAPSIZE]);
	void GenerateLabVertexData(const unsigned short BitMap[LABSIZE]);
	void GenerateForestVertexData(const unsigned short BitMap[FORESTMAPSIZE]);

    void AddVert(vec2 objectPos, float objectAngle, vec2 objectScale, vec2 aUVscale, vec2 aUVoffset);

	void SetIsReverse(bool isreverse);

private:

	TileMap* m_MyTileMap;
	ResourceManager* m_MyResourceManager;

	bool IsReversed;

	std::vector<VertexFormat> m_BaseTileVerts = {
	VertexFormat(vec2(0.0f,  0.0f), MyColor(255, 255, 255, 255), vec2(0.0f, 0.0f)),
	VertexFormat(vec2(0.0f,  1.0f), MyColor(255, 255, 255, 255), vec2(0.0f, 1.0f)),
	VertexFormat(vec2(1.0f,  0.0f), MyColor(255, 255, 255, 255), vec2(1.0f, 0.0f)),
	VertexFormat(vec2(1.0f,  1.0f), MyColor(255, 255, 255, 255), vec2(1.0f, 1.0f))
	};
	std::vector<VertexFormat> m_BaseTileVertsReverse = {
	VertexFormat(vec2(1.0f,  0.0f), MyColor(255, 255, 255, 255), vec2(1.0f, 0.0f)),
	VertexFormat(vec2(1.0f,  1.0f), MyColor(255, 255, 255, 255), vec2(1.0f, 1.0f)),
	VertexFormat(vec2(0.0f,  0.0f), MyColor(255, 255, 255, 255), vec2(0.0f, 0.0f)),
	VertexFormat(vec2(0.0f,  1.0f), MyColor(255, 255, 255, 255), vec2(0.0f, 1.0f))
	};
};