#include "util.h"
#include <Windows.h>
#include <stdio.h>
#include <spdlog/spdlog.h>

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

void util::fatal_error(const char* fmt, ...)
{
    char buf[0x800];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

	spdlog::error("{}", buf);

    MessageBoxA(nullptr, buf, "Winter: Fatal Error", MB_OK | MB_ICONERROR);
    std::exit(EXIT_FAILURE);
}