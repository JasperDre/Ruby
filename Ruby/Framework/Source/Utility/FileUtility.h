#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>

namespace FileUtility
{
    static unsigned int GetFileSize(const std::string& aPath)
    {
        return static_cast<unsigned int>(std::filesystem::file_size(aPath));
    }

    static bool IsFileValid(const std::string& aPath)
    {
        return std::filesystem::exists(aPath);
    }

    static std::string GetExtensionFromPath(const std::string& aPath)
    {
        const std::size_t extensionStartIndex = aPath.find_last_of('.') + 1;
        return aPath.substr(extensionStartIndex, aPath.length() - extensionStartIndex);
    }

    static std::string GetNameFromPath(const std::string& aPath)
    {
        const std::size_t nameStartIndex = aPath.find_last_of("/\\") + 1;
        const std::size_t extensionStartIndex = aPath.find_last_of('.');
        return aPath.substr(nameStartIndex, aPath.length() - nameStartIndex - (aPath.length() - extensionStartIndex));
    }

    static std::string GetDirectoryFromPath(const std::string& aPath)
    {
        const std::size_t lastSlashIndex = aPath.find_last_of("/\\");
        return aPath.substr(0, lastSlashIndex + 1);
    }

    static std::string ReadFile(const std::string& aPath)
    {
        std::ifstream fileStream(aPath.c_str(), std::ios::in);
        if (!fileStream.is_open())
            return "";

        std::stringstream sourceStringStream;
        sourceStringStream << fileStream.rdbuf();

        fileStream.close();

        return sourceStringStream.str();
    }

    static char* ReadFileIntoBuffer(const std::string& aPath)
    {
        const std::string source = ReadFile(aPath);
        const unsigned int bufferSize = source.length() + 1;
        char* buffer = new char[bufferSize];
        strcpy_s(buffer, bufferSize, source.c_str());

        return buffer;
    }

    static char* ReadBinaryFileIntoBuffer(const std::string& aPath)
    {
        FILE* fileStream;
        const errno_t error = fopen_s(&fileStream, aPath.c_str(), "rb");
        if (error != 0)
            return nullptr;

        const unsigned int fileSize = GetFileSize(aPath);
        char* buffer = new char[fileSize];
        std::fread(buffer, sizeof(buffer[0]), fileSize, fileStream);

        std::fclose(fileStream);

        return buffer;
    }
}