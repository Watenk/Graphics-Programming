#pragma once

#include <string>

class FileUtil {
public:
    /**
     * Reads the contents of a file.
     * @param filePath The path to the file.
     * @return The contents of the file.
     */
    static std::string parsePath(const std::string& filepath);
};