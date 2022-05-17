#include "ResourceManager.h"

#include <cassert>
#include <rapidjson/document.h>

#include "GameplayHelpers/TileMap.h"
#include "Utility/DebugUtility.h"
#include "Utility/FileUtility.h"

ResourceManager::ResourceManager()
	: myTileMap(nullptr)
{}

ResourceManager::~ResourceManager()
{
	myAnimationsMap.clear();
}

void ResourceManager::UnpackJson(const std::string& aFilepath, TileMap* aTileMap)
{
	const bool isFileValid = FileUtility::IsFileValid(aFilepath);
	assert(isFileValid);
	if (!isFileValid)
		return;

	const char* buffer = FileUtility::ReadFileIntoBuffer(aFilepath);
	rapidjson::Document document;
	document.Parse(buffer);
	if (document.HasParseError())
	{
		DebugUtility::OutputMessage("Failed to read json");
		return;
	}

	const int textureWidth = document["width"].GetInt();
	const int textureHeight = document["height"].GetInt();

	myTextureSize.emplace_back(Vector2Int(textureWidth, textureHeight));

	const rapidjson::Value& frames = document["Files"];
	//Extract the Array of Frames from the root
	//const cJSON* frames = cJSON_GetObjectItem(root, "Files");
	//Get the number of element in the Array of Frames

	//Cycle through the Array of Frames and input the Size and UVCoord into the local map
	for (unsigned int i = 0; i < frames.Size(); i++)
	{
		const rapidjson::Value& frame = frames[i];
		//store the name of the frame in a string
		std::string frameName = frame["filename"].GetString();

		//get the size of the frame
		const int height = frame["trimh"].GetInt();
		const int width = frame["trimw"].GetInt();
		//get the origin of the frame on the texture
		const int x = frame["posx"].GetInt();
		const int y = frame["posy"].GetInt();

		if (aFilepath.find("ExtrasTileSet.json") == std::string::npos)
		{
			//Check to see if the frame attribute is an animation sprite
			if (height == 21 && width == 14)
			{
				//create a frame with the attributes from the JSON file
				Frame myNewFrame = Frame(Vector2Float(static_cast<float>(x), static_cast<float>(y)), Vector2Float(static_cast<float>(width), static_cast<float>(height)));

				myAnimationsMap.insert(std::pair<std::string, Frame>(frameName, myNewFrame));
			}
			//Then check to see if Frame attribute is a tile
			if (height == 16 && width == 16)
			{
				//create a frame with the attributes from the JSON file
				const Frame myNewFrame = Frame(Vector2Float(static_cast<float>(x), static_cast<float>(y)), Vector2Float(static_cast<float>(width), static_cast<float>(height)));

				//send the frame name and its attributes to the TileMap for processing
				aTileMap->AddTile(frameName, myNewFrame);
			}
		}
		else
		{
			//create a frame with the attributes from the JSON file
			const Frame myNewFrame = Frame(Vector2Float(static_cast<float>(x), static_cast<float>(y)), Vector2Float(static_cast<float>(width), static_cast<float>(height)));

			//send the frame name and its attributes to the TileMap for processing
			aTileMap->AddTile(frameName, myNewFrame);
		}
	}

	delete[] buffer;
}

Frame ResourceManager::GetFrameAtIndex(const std::string& anIndex) const
{
	return myAnimationsMap.find(anIndex)->second;
}

Vector2Int ResourceManager::GetTextureSize(int anIndex) const
{
	return myTextureSize.at(anIndex);
}

unsigned int ResourceManager::GetTexture(TextureHandle aTextureName) const
{
	return myTextures.find(aTextureName)->second;
}

void ResourceManager::HoldTexture(TextureHandle aTextureName, unsigned int aTexture)
{
	myTextures.insert(std::pair<TextureHandle, unsigned int>(aTextureName, aTexture));
}
