#pragma once

#include <vector>

#include "Constants.h"
#include "Mesh.h"
#include "Math/Color.h"

class TileMap;
class ResourceManager;

class Canvas : public Mesh
{
public:
	Canvas(TileMap* aTileMap, ResourceManager* aResourceManager);
	~Canvas() override = default;

	void GeneratePalletVertexData(const unsigned short BitMap[MAPSIZE]);
	void GenerateLabVertexData(const unsigned short BitMap[LABSIZE]);
	void GenerateForestVertexData(const unsigned short BitMap[FORESTMAPSIZE]);
	void AddVert(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float aUVscale, Vector2Float aUVoffset);

	void SetIsReverse(bool isreverse);

private:
	TileMap* myTileMap;
	ResourceManager* myResourceManager;
	bool myIsReversed;

	std::vector<VertexFormat> m_BaseTileVerts =
	{
		VertexFormat(Vector2Float(0.0f, 0.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 0.0f)),
		VertexFormat(Vector2Float(0.0f, 1.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 1.0f)),
		VertexFormat(Vector2Float(1.0f, 0.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 0.0f)),
		VertexFormat(Vector2Float(1.0f, 1.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 1.0f))
	};

	std::vector<VertexFormat> m_BaseTileVertsReverse =
	{
		VertexFormat(Vector2Float(1.0f, 0.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 0.0f)),
		VertexFormat(Vector2Float(1.0f, 1.0f), Color(255, 255, 255, 255), Vector2Float(1.0f, 1.0f)),
		VertexFormat(Vector2Float(0.0f, 0.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 0.0f)),
		VertexFormat(Vector2Float(0.0f, 1.0f), Color(255, 255, 255, 255), Vector2Float(0.0f, 1.0f))
	};
};