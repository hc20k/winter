#include "ceg.h"
#include "logging.h"
#include "memory.h"
#include <Windows.h>
#include <vector>
#include <iostream>
#include "hooking.h"
#include <DbgHelp.h>

#pragma comment(lib, "Dbghelp.lib")

uintptr_t dll_base = 0;

uintptr_t dll_offset(uintptr_t offset) {
	return dll_base + offset - 0x10000000;
}

std::vector<const char*> get_module_exports(HMODULE module) {
	ULONG size;
	auto exports = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(ImageDirectoryEntryToData(module, TRUE, IMAGE_DIRECTORY_ENTRY_EXPORT, &size));
	if (!exports) {
		spdlog::error("Failed to get export directory");
		return {};
	}

	auto names = reinterpret_cast<PDWORD>(reinterpret_cast<BYTE*>(module) + exports->AddressOfNames);
	std::vector<const char*> export_names;
	for (DWORD i = 0; i < exports->NumberOfNames; ++i) {
		auto name = reinterpret_cast<const char*>(reinterpret_cast<BYTE*>(module) + names[i]);
		export_names.push_back(name);
	}
	return export_names;
}

uintptr_t nightly_hook_calls[] = {
	0x1001AB2F, // top level exception filter
	//0x1001AB39, // console
	0x1001AB34, // show system link, change version name
	0x1001AB3E, // sets up, r_noborder
	0x1001AB43, // some steam stuff? idk, and commands
	0x1001AB48, // localization, text modification
	0x1001AB4D, // handles hks lua errors
	0x1001AB52, // not sure...
	0x1001AB57, // nothing
	0x1001AB5C, // bot clan tags
	0x1001AB61, // nothing
	//0x1001AB66 // dlc (we can leave this one)
};

// Dogshit code ahead!!
// Literally loads the redacted steam_api.dll and calls the function to disable CEG
// Then replaces all goldberg emu steam_api.dll exports with the ones from the redacted steam_api.dll

void ceg::init() {
	dll_base = (uintptr_t)LoadLibrary("winter/ceg.dll"); // Nightly0625 steam_api.dll
	if (dll_base == NULL) {
		MessageBox(NULL, "Failed to load winter/ceg.dll", "Error", MB_OK | MB_ICONERROR);
		ExitProcess(1);
		return;
	}

	memory::nop(dll_offset(0x1001AC7D), 6); // don't jump back to the original entrypoint

	// remove all hooks from nightly
	for (auto& call : nightly_hook_calls) {
		hooking::nop(dll_offset(call), 5);
	}

	hooking::invoke<int>(dll_offset(0x1001ABA0)); // fuck ceg !

	auto steam_api = GetModuleHandleA("steam_api.dll");
	assert(steam_api != NULL);

	for (auto& name : get_module_exports(steam_api)) {
		auto address = GetProcAddress((HMODULE)dll_base, name);
		if (address) {
			auto steam_api_address = GetProcAddress(steam_api, name);
			hooking::qjmp(steam_api_address, address);
		}
	}
}