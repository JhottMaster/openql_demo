#include "file_utils.hpp"

std::string FileUtils::ReadString(const char * file_path) {
	std::ifstream fileStream (file_path, std::ios::in);
	std::string contents;
	if(fileStream.is_open()) {
		std::stringstream sstr;
		sstr << fileStream.rdbuf();
		contents = sstr.str();
		fileStream.close();
	} else {
		printf("Could not read file '%s'.\n", file_path);
	}
	return contents;
}

char const * FileUtils::ReadStringToPointer(const char * file_path) {
	return FileUtils::ReadString(file_path).c_str();
}
