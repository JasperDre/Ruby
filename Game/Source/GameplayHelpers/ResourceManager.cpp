#include "GamePCH.h"

#include "ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include <fstream>
#include <map>

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	m_AnimationsMap.clear();
}

void ResourceManager::UnpackJson(const std::string& JSONfilename, TileMap* aTileMap)
{
	bool DoesExist = true;
	DWORD fileAttributes = GetFileAttributesA(JSONfilename.c_str());
	DoesExist = (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY));

	assert(DoesExist == true);

	if (DoesExist == true)
	{
		//open the input stream
		std::ifstream InputStream;
		InputStream.open(JSONfilename.c_str(), std::ifstream::in | std::ifstream::binary);

		if (InputStream.is_open() == true)
		{
			//find the length of the file
			InputStream.seekg(0, InputStream.end);		//seek the end
			int size = InputStream.tellg();				//read the position of the last byte
			InputStream.seekg(0, InputStream.beg);		//go back to the beginning

			//Before reading file we need to allocate a char array of the correct size
			char* buffer = new char[size];
			InputStream.read((char*)buffer, size);

			//Parse the Buffer into a cJSON object
			cJSON* root = cJSON_Parse(buffer);
			if (root)
			{
				int TextureWidth = cJSON_GetObjectItem(root, "width")->valueint;
				int TextureHeight = cJSON_GetObjectItem(root, "height")->valueint;

				m_MyTextureSize.push_back(ivec2(TextureWidth, TextureHeight));

				//Extract the Array of Frames from the root
				cJSON* frames = cJSON_GetObjectItem(root, "Files");
				//Get the number of element in the Array of Frames
				int num_frames = cJSON_GetArraySize(frames);

				//Cycle through the Array of Frames and input the Size and UVCoord into the local map
				for (int i = 0; i < num_frames; i++)
				{
					cJSON* aframe = cJSON_GetArrayItem(frames, i);
					//store the name of the frame in a string
					std::string fname = cJSON_GetObjectItem(aframe, "filename")->valuestring;

					char* str = cJSON_Print(aframe);

					//get the size of the frame
					int height = cJSON_GetObjectItem(aframe, "trimh")->valueint;
					int width = cJSON_GetObjectItem(aframe, "trimw")->valueint;
					//get the origin of the frame on the texture
					int X = cJSON_GetObjectItem(aframe, "posx")->valueint;
					int Y = cJSON_GetObjectItem(aframe, "posy")->valueint;
					
					if (JSONfilename != "Data/Textures/ExtrasTileSet.json")
					{
						//Check to see if the frame attribute is an animation sprite
						if (height == 21 && width == 14)
						{
							//create a frame with the attributes from the JSON file
							Frame myNewFrame = Frame(vec2((float)X, (float)Y), vec2((float)width, (float)height));

							m_AnimationsMap.insert(std::pair<std::string, Frame>(fname, myNewFrame));
						}
						//Then check to see if Frame attribute is a tile
						if (height == 16 && width == 16)
						{
							//create a frame with the attributes from the JSON file
							Frame myNewFrame = Frame(vec2((float)X, (float)Y), vec2((float)width, (float)height));

							//send the frame name and its attributes to the TileMap for processing
							aTileMap->AddTile(fname, myNewFrame);
						}
					}
					else
					{
						//create a frame with the attributes from the JSON file
						Frame myNewFrame = Frame(vec2((float)X, (float)Y), vec2((float)width, (float)height));

						//send the frame name and its attributes to the TileMap for processing
						aTileMap->AddTile(fname, myNewFrame);
					}
				}

				//close the input stream
				InputStream.close();

			}
			delete[] buffer;
		}


	}
}

Frame ResourceManager::GetFrameat(const std::string & anIndex)
{
	return m_AnimationsMap.find(anIndex)->second;
}

ivec2 ResourceManager::GetTextureSize(int anIndex)
{
	return m_MyTextureSize.at(anIndex);
}

GLuint ResourceManager::GetaTexture(TextureHandle aTextureName)
{
	return m_MyTextures.find(aTextureName)->second;
}

void ResourceManager::HoldTexture(TextureHandle aTextureName, GLuint aTexture)
{
	m_MyTextures.insert(std::pair<TextureHandle, GLuint>(aTextureName, aTexture));
}
