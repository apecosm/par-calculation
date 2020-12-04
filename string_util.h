#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <vector>

std::string getFileName(std::string filePath);
std::string getDirName(std::string filePath);
std::vector<std::string> get_files(const char *file_prefix);

#endif
