#ifndef __FILE_UTILS_INCLUDED__
#define __FILE_UTILS_INCLUDED__

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class FileUtils {
  public:
    static std::string ReadString(const char * file_path);
    static char const * ReadStringToPointer(const char * file_path);
};

#endif 