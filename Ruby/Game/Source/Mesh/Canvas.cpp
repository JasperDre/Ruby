#include "GamePCH.h"
#include "Canvas.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

Canvas::Canvas(TileMap* aTileMap, ResourceManager* aResourceManager)
{
	m_MyTileMap = aTileMap;
	m_MyResourceManager = aResourceManager;
}
Canvas::~Canvas()
{

}
void Canvas::GeneratePalletVertexData(const unsigned short BitMap[MAPSIZE])
{
	//create the masks to find the Tile Type and Variant
	unsigned short TileMask = 15;
	unsigned short VariantMask = 1008;

	for (int i = 0; i < MAPSIZE; i++)
	{
		int j = 0;
		if ((i / NUM_COLUMNS) % 2 == 1)
		{
			SetIsReverse(true);

			j = (NUM_COLUMNS - 1) - (i % NUM_COLUMNS);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[((i / NUM_COLUMNS) * NUM_COLUMNS) + j] & TileMask;
			unsigned short VariantSelecter = BitMap[((i / NUM_COLUMNS) * NUM_COLUMNS) + j] & VariantMask;

			if (Tile_Type(TileSelecter) != Town_Null_Wall_ && Tile_Type(TileSelecter) != Town_Null_Door_)
			{

				//create a temp TileInfo struct to access the attributes
				TileInfo atile = m_MyTileMap->GetTileFromPalletMap(Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.MyVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				vec2 aVOffset = vec2((aframe.myOrigin.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.myOrigin.y / m_MyResourceManager->GetTextureSize(0).y));
				vec2 aUVScale = vec2((aframe.mySize.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.mySize.y / m_MyResourceManager->GetTextureSize(0).y));

				//set up the position
				vec2 aposition = vec2(((((i / NUM_COLUMNS) * NUM_COLUMNS) + j) % NUM_COLUMNS) * TILESIZE, ((((i / NUM_COLUMNS) * NUM_COLUMNS) + j) / NUM_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, vec2(TILESIZE, TILESIZE), aUVScale, aVOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[i] & TileMask;
			unsigned short VariantSelecter = BitMap[i] & VariantMask;

			if (Tile_Type(TileSelecter) != Town_Null_Wall_ && Tile_Type(TileSelecter) != Town_Null_Door_)
			{
				//create a temp TileInfo struct to access the attributes
				TileInfo atile = m_MyTileMap->GetTileFromPalletMap(Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.MyVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				vec2 aUVOffset = vec2((aframe.myOrigin.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.myOrigin.y / m_MyResourceManager->GetTextureSize(0).y));
				vec2 aUVScale = vec2((aframe.mySize.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.mySize.y / m_MyResourceManager->GetTextureSize(0).y));

				//set up the position
				vec2 aposition = vec2((i % NUM_COLUMNS) * TILESIZE, (i / NUM_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, vec2(TILESIZE, TILESIZE), aUVScale, aUVOffset);
			}
		}
	}
}
void Canvas::GenerateLabVertexData(const unsigned short BitMap[LABSIZE])
{
	//create the masks to find the Tile Type and Variant
	unsigned short TileMask = 15;
	unsigned short VariantMask = 1008;

	for (int i = 0; i < LABSIZE; i++)
	{
		int j = 0;
		if ((i / NUM_LAB_COLUMNS) % 2 == 1)
		{
			SetIsReverse(true);

			j = (NUM_LAB_COLUMNS - 1) - (i % NUM_LAB_COLUMNS);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j] & TileMask;
			unsigned short VariantSelecter = BitMap[((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j] & VariantMask;

			if (OakLab_Tile_Type(TileSelecter) != Oak_Lab_NullWall_ && OakLab_Tile_Type(TileSelecter) != Oak_Lab_NullDoor_)
			{
				//create a temp TileInfo struct to access the attributes
				TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(OakLab_Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.MyVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				vec2 aVOffset = vec2((aframe.myOrigin.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.myOrigin.y / m_MyResourceManager->GetTextureSize(1).y));
				vec2 aUVScale = vec2((aframe.mySize.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.mySize.y / m_MyResourceManager->GetTextureSize(1).y));

				//set up the position
				vec2 aposition = vec2(((((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j) % NUM_LAB_COLUMNS) * TILESIZE, ((((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j) / NUM_LAB_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, vec2(TILESIZE, TILESIZE), aUVScale, aVOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[i] & TileMask;
			unsigned short VariantSelecter = BitMap[i] & VariantMask;

			if (OakLab_Tile_Type(TileSelecter) != Oak_Lab_NullWall_ && OakLab_Tile_Type(TileSelecter) != Oak_Lab_NullDoor_)
			{
				//create a temp TileInfo struct to access the attributes
				TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(OakLab_Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.MyVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				vec2 aUVOffset = vec2((aframe.myOrigin.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.myOrigin.y / m_MyResourceManager->GetTextureSize(1).y));
				vec2 aUVScale = vec2((aframe.mySize.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.mySize.y / m_MyResourceManager->GetTextureSize(1).y));

				//set up the position
				vec2 aposition = vec2((i % NUM_LAB_COLUMNS) * TILESIZE, (i / NUM_LAB_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, vec2(TILESIZE, TILESIZE), aUVScale, aUVOffset);
			}
		}
	}
}
void Canvas::GenerateForestVertexData(const unsigned short BitMap[FORESTMAPSIZE])
{
	//create the masks to find the Tile Type and Variant
	unsigned short TileMask = 15;
	unsigned short VariantMask = 1008;

	for (int i = 0; i < FORESTMAPSIZE; i++)
	{
		int j = 0;
		if ((i / NUM_FOREST_COLUMNS) % 2 == 1)
		{
			SetIsReverse(true);

			j = (NUM_FOREST_COLUMNS - 1) - (i % NUM_FOREST_COLUMNS);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j] & TileMask;
			unsigned short VariantSelecter = BitMap[((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j] & VariantMask;

			if (Forest_Tile_Type(TileSelecter) != Forest_Null_Wall && Forest_Tile_Type(TileSelecter) != Forest_Null_Door)
			{
				//create a temp TileInfo struct to access the attributes
				TileInfo atile = m_MyTileMap->GetTileFromWoodsMap(Forest_Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.MyVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				vec2 aVOffset = vec2((aframe.myOrigin.x / m_MyResourceManager->GetTextureSize(3).x), (aframe.myOrigin.y / m_MyResourceManager->GetTextureSize(3).y));
				vec2 aUVScale = vec2((aframe.mySize.x / m_MyResourceManager->GetTextureSize(3).x), (aframe.mySize.y / m_MyResourceManager->GetTextureSize(3).y));

				//set up the position
				vec2 aposition = vec2(((((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j) % NUM_FOREST_COLUMNS) * TILESIZE, ((((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j) / NUM_FOREST_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, vec2(TILESIZE, TILESIZE), aUVScale, aVOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[i] & TileMask;
			unsigned short VariantSelecter = BitMap[i] & VariantMask;

			if (Forest_Tile_Type(TileSelecter) != Forest_Null_Wall && Forest_Tile_Type(TileSelecter) != Forest_Null_Door)
			{
				//create a temp TileInfo struct to access the attributes
				TileInfo atile = m_MyTileMap->GetTileFromWoodsMap(Forest_Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.MyVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				vec2 aUVOffset = vec2((aframe.myOrigin.x / m_MyResourceManager->GetTextureSize(3).x), (aframe.myOrigin.y / m_MyResourceManager->GetTextureSize(3).y));
				vec2 aUVScale = vec2((aframe.mySize.x / m_MyResourceManager->GetTextureSize(3).x), (aframe.mySize.y / m_MyResourceManager->GetTextureSize(3).y));

				//set up the position
				vec2 aposition = vec2((i % NUM_FOREST_COLUMNS) * TILESIZE, (i / NUM_FOREST_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, vec2(TILESIZE, TILESIZE), aUVScale, aUVOffset);
			}
		}
	}
}
void Canvas::AddVert(vec2 objectPos, float objectAngle, vec2 objectScale, vec2 aUVscale, vec2 aUVoffset)
{
	const float radians = objectAngle / 180.0f * PI;

	for (unsigned int i = 0; i < m_BaseTileVerts.size(); i++)
	{
		if (IsReversed == true)
		{
			vec2 finalPos = m_BaseTileVertsReverse.at(i).m_Pos;

			finalPos *= objectScale;

			finalPos = vec2(finalPos.x * cos(radians) - finalPos.y * sin(radians),
				finalPos.x * sin(radians) + finalPos.y * cos(radians));

			finalPos += objectPos;

			vec2 UVTemp = m_BaseTileVertsReverse.at(i).m_UV;

			UVTemp *= aUVscale;

			UVTemp += aUVoffset;

			VertexFormat aVert = VertexFormat(vec2(finalPos), MyColor(m_BaseTileVertsReverse.at(i).m_Color), vec2(UVTemp));

			m_CanvasVerts.push_back(aVert);
		}
		else
		{
			vec2 finalPos = m_BaseTileVerts.at(i).m_Pos;

			finalPos *= objectScale;

			finalPos = vec2(finalPos.x * cos(radians) - finalPos.y * sin(radians),
				finalPos.x * sin(radians) + finalPos.y * cos(radians));

			finalPos += objectPos;

			vec2 UVTemp = m_BaseTileVerts.at(i).m_UV;

			UVTemp *= aUVscale;

			UVTemp += aUVoffset;

			VertexFormat aVert = VertexFormat(vec2(finalPos), MyColor(m_BaseTileVerts.at(i).m_Color), vec2(UVTemp));

			m_CanvasVerts.push_back(aVert);
		}
	}
}

void Canvas::SetIsReverse(bool isreverse)
{
	IsReversed = isreverse;
}
