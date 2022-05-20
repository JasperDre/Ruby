#include "TilemapLoader.h"

#include "tileson.hpp"

void TilemapLoader::Load(const std::string& aTilemapPath, const std::string& aTilesetPath)
{
    tson::Tileson tileson;
    const bool isValid = std::filesystem::exists(aTilemapPath);
    const std::unique_ptr<tson::Map> map = tileson.parse(std::filesystem::path(aTilemapPath));
    const tson::ParseStatus result = map->getStatus();
}