
#include "FileUtil.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

std::string FileUtil::parsePath(const std::string& filepath){
    std::ifstream stream(filepath);
    if (!stream.is_open()) {
        std::cerr << "Error: Failed to open file " << filepath << std::endl;
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Current working directory: " << currentPath << std::endl;
    }

    std::stringstream ss;
    std::string line;
    while (getline(stream, line)){
        ss << line << '\n';
    }

    stream.close();
    return ss.str();
}