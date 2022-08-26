///
/// \Authors Hunter, Davis, Patience
/// \file FileManager.hh
/// \note A file manager with static methods for listing directories of files and reading in files as strings
///

#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <regex>

/// <summary>
/// A class with static methods related to file management.
/// Allows getting contents from a file and getting a list of header files from a directory.
/// </summary>
class FileManager {
public:

    // Static Methods

    /// <summary>
    /// Reads the contents from a given filename
    /// </summary>
    /// <param name="fileName">The name of the file to read the contents from</param>
    /// <returns>The contents of the file as a string</returns>
    static std::string readFile(std::string fileName) {
        // Create a stream for a file with the given fileName
        std::ifstream fileIn(fileName);

        // Create a stream to store what is read from the file
        std::stringstream fileContents;
        fileContents << fileIn.rdbuf();

        // Return the contents of the stream as a string
        return fileContents.str();
    }

    /// <summary>
    /// Gets the file paths for all of the header files in the specified directory
    /// </summary>
    /// <param name="srcDirectory">The directory to search for header files in</param>
    /// <param name="recursive">Decides whether or not to search subdirectories in the srcDirectory (true -> search subdirectories)</param>
    /// <returns>A vector of filepaths to header files found in the srcDirectory</returns>
    static std::vector<std::string> getFilePaths(std::string srcDirectory, bool recursive) {
        // If recursive is true, use recursive_directory_iterator to search all subfolders in the specified directory
        if (recursive) {
            return getHeaderFiles(std::filesystem::recursive_directory_iterator(srcDirectory));
        }
        // Otherwise use a normal directory_iterator
        else {
            return getHeaderFiles(std::filesystem::directory_iterator(srcDirectory));
        }
    }

private:
    // Static Helper Methods

    /// <summary>
    /// Finds the header files using the given directory iterator
    /// </summary>
    /// <param name="directoryIterator">The directory editor to use for searching for header files (either directory_iterator or recursive_directory_iterator)</param>
    /// <returns>A vector of filepaths to header files found in the directoryIterator</returns>
    static std::vector<std::string> getHeaderFiles(auto directoryIterator) {
        std::vector<std::string> filePaths;

        // Loop through the contents of the directory
        for (const auto& entry : directoryIterator) {
            std::string path = entry.path().string();

            // If the entry isn't a directory and is a header file, add it to the list to return
            if (!entry.is_directory() && regex_match(path, std::regex(R"(.*\.(?:h|hh|hxx)$)"))) {
                filePaths.push_back(path);
            }
        }

        return filePaths;
    }
};
