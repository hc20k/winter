#include "util.h"
#include <Windows.h>

bool util::file_exists(const char* filename) {
	DWORD fileAttr = GetFileAttributesA(filename);
	if (fileAttr == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	return true;
}

const char* util::get_executable_path() {
	static char path[MAX_PATH];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	return path;
}