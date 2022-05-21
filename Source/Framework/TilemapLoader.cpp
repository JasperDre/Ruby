#include "TilemapLoader.h"

#include "tileson.hpp"
#include "Utility/DebugUtility.h"

std::vector<TilemapLoader::Tile> TilemapLoader::Load(const std::filesystem::path& aTilemapPath)
{
    std::vector<TilemapLoader::Tile> tiles;
    tson::Tileson tileson;
    const std::unique_ptr<tson::Map> map = tileson.parse(std::filesystem::path(aTilemapPath));
    const tson::ParseStatus status = map->getStatus();
    if (status != tson::ParseStatus::OK)
    {
        DebugUtility::OutputMessage("Failed to load %s", aTilemapPath.c_str());
        return tiles;
    }

    for (tson::Layer& layer : map->getLayers())
    {
        if (layer.getType() == tson::LayerType::TileLayer)
        {
            for (const auto& tuple : layer.getTileObjects())
            {
                tson::TileObject tileObject = tuple.second;
                const tson::Tileset* tileset = tileObject.getTile()->getTileset();
                const tson::Rect drawingRect = tileObject.getDrawingRect();
                const tson::Vector2f position = tileObject.getPosition();
                const std::filesystem::path tilesetPath = std::filesystem::path(std::filesystem::path("../") / tileset->getImage().filename());
                const bool isCollidable = tileObject.getTile()->get<bool>("IsCollidable");
                const uint32_t identifier = tileObject.getTile()->getGid();

                Tile tile;
                tile.myTilesetPath = tilesetPath;
                tile.myIdentifier = identifier;
                tile.myRectangle = Rectangle(drawingRect.x, drawingRect.y, drawingRect.width, drawingRect.height);
                tile.myPosition = Vector2Float(position.x, position.y);
                tile.myIsCollidable = isCollidable;
                tiles.emplace_back(tile);
            }
        }
    }

    return tiles;
}