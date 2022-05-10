#include "GamePCH.h"
#include "ResourceManager.h"

#include <fstream>

#include "GameplayHelpers/TileMap.h"
#include "Utility/FileUtility.h"

ResourceManager::ResourceManager()
	: m_MyTileMap(nullptr)
{}

ResourceManager::~ResourceManager()
{
	m_AnimationsMap.clear();
}

void ResourceManager::UnpackJson(const std::string& JSONfilename, TileMap* aTileMap)
{
	const bool isFileValid = FileUtility::IsFileValid(JSONfilename);
	assert(isFileValid);
	if (!isFileValid)
		return;

	std::ifstream InputStream;
	InputStream.open(JSONfilename.c_str(), std::ifstream::in | std::ifstream::binary);
	if (!InputStream.is_open())
		return;

	//Before reading file we need to allocate a char array of the correct size
	const int fileSize = FileUtility::GetFileSize(JSONfilename);
	char* buffer = new char[fileSize];
	InputStream.read(buffer, fileSize);

	//Parse the Buffer into a cJSON object
	cJSON* root = cJSON_Parse(buffer);
	if (root)
	{
		int textureWidth = cJSON_GetObjectItem(root, "width")->valueint;
		int textureHeight = cJSON_GetObjectItem(root, "height")->valueint;

		m_MyTextureSize.emplace_back(ivec2(textureWidth, textureHeight));

		//Extract the Array of Frames from the root
		cJSON* frames = cJSON_GetObjectItem(root, "Files");
		//Get the number of element in the Array of Frames
		int num_frames = cJSON_GetArraySize(frames);

		//Cycle through the Array of Frames and input the Size and UVCoord into the local map
		for (int i = 0; i < num_frames; i++)
		{
			cJSON* frame = cJSON_GetArrayItem(frames, i);
			//store the name of the frame in a string
			std::string frameName = cJSON_GetObjectItem(frame, "filename")->valuestring;

			//get the size of the frame
			int height = cJSON_GetObjectItem(frame, "trimh")->valueint;
			int width = cJSON_GetObjectItem(frame, "trimw")->valueint;
			//get the origin of the frame on the texture
			int x = cJSON_GetObjectItem(frame, "posx")->valueint;
			int y = cJSON_GetObjectItem(frame, "posy")->valueint;

			if (JSONfilename.find("ExtrasTileSet.json") == std::string::npos)
			{
				//Check to see if the frame attribute is an animation sprite
				if (height == 21 && width == 14)
				{
					//create a frame with the attributes from the JSON file
					Frame myNewFrame = Frame(vec2((float)x, (float)y), vec2((float)width, (float)height));

					m_AnimationsMap.insert(std::pair<std::string, Frame>(frameName, myNewFrame));
				}
				//Then check to see if Frame attribute is a tile
				if (height == 16 && width == 16)
				{
					//create a frame with the attributes from the JSON file
					Frame myNewFrame = Frame(vec2((float)x, (float)y), vec2((float)width, (float)height));

					//send the frame name and its attributes to the TileMap for processing
					aTileMap->AddTile(frameName, myNewFrame);
				}
			}
			else
			{
				//create a frame with the attributes from the JSON file
				Frame myNewFrame = Frame(vec2((float)x, (float)y), vec2((float)width, (float)height));

				//send the frame name and its attributes to the TileMap for processing
				aTileMap->AddTile(frameName, myNewFrame);
			}
		}

		InputStream.close();
	}

	delete[] buffer;
}

Frame ResourceManager::GetFrameat(const std::string & anIndex) const
{
	return m_AnimationsMap.find(anIndex)->second;
}

ivec2 ResourceManager::GetTextureSize(int anIndex) const
{
	return m_MyTextureSize.at(anIndex);
}

GLuint ResourceManager::GetaTexture(TextureHandle aTextureName) const
{
	return m_MyTextures.find(aTextureName)->second;
}

void ResourceManager::HoldTexture(TextureHandle aTextureName, GLuint aTexture)
{
	m_MyTextures.insert(std::pair<TextureHandle, GLuint>(aTextureName, aTexture));
}
