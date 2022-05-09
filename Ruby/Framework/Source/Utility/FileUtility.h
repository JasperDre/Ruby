#pragma once

#include <filesystem>
#include <string>

static int GetFileSize(const std::string& aFilepath)
{
    return static_cast<int>(std::filesystem::file_size(aFilepath));
}

static bool IsFileValid(const std::string& aFilepath)
{
    return std::filesystem::exists(aFilepath);
}