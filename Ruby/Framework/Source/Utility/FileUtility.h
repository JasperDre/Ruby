#pragma once

#include <filesystem>
#include <string>

namespace FileUtility
{
    static int GetFileSize(const std::string& aPath)
    {
        return static_cast<int>(std::filesystem::file_size(aPath));
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
}