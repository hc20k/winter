#include "patches.h"
#include "memory.h"
#include "logging.h"
#include "game.h"
#include <MinHook.h>
#include <iostream>
#include "hooking.h"
#include <filesystem>
#include "util.h"
#include <ErrorRep.h>

#pragma comment(lib, "Faultrep.lib")


hooking::detour db_find_xasset_header;
hooking::detour db_try_load_xfile_internal;
hooking::detour com_init_ui_and_common_xassets;
hooking::detour ki_kore_load;
hooking::detour db_load_xfile;
hooking::detour com_error;
hooking::detour top_level_excecution_filter;
hooking::detour db_authload_init;
hooking::detour db_authload_getiv;
hooking::detour db_authload_analyzedata;
hooking::detour validate_file_header_hook;
hooking::detour db_authload_add_checksum_hook;
hooking::detour db_reliable_fsopen_readonly_hook;
hooking::detour db_load_xassets;


bool is_loading_unsigned = false;

game::XAssetHeader db_find_xasset_header_stub(int type, const char* a2, char a3, int a4) {
	spdlog::info("Loading asset '{}' of type {}", a2, type);
	auto result = db_find_xasset_header.invoke<game::XAssetHeader>(type, a2, a3, a4);
	return result;
}

int db_try_load_xfile_internal_stub(const char* name, int a2, int a3) {
	return db_try_load_xfile_internal.invoke<int>(name, a2, a3);
}

bool load_unsigned_fastfile(const char* path, int f, const char* name, game::XBlock* blocks, void (_cdecl* interrupt)(), uint8_t* buf, int allocType, int flags, int requiredVersion, unsigned int desiredReadBytes) {

	// g_load = 1299E00
	game::DB_LoadData& g_load = *reinterpret_cast<game::DB_LoadData*>(0x1299E00);
	int& g_numStreams = *reinterpret_cast<int*>(0xD3EB2C);

	memset(&g_load, 0, sizeof(game::DB_LoadData));

	g_load.f = f;
	g_load.flags = flags;
	g_load.ioBuffer = buf;
	g_load.filename = name;
	g_load.blocks = blocks;
	g_load.interrupt = interrupt;
	g_load.allocType = allocType;
	g_load.ioBufferOffset = 0;
	g_load.next_buffer = 0;
	g_load.abort = 0;
	g_load.requiredVersion = requiredVersion;

	auto offset = hooking::invoke<uint32_t>(0x4120E0, g_load.f); // Stream_Easy_Tell
	spdlog::info("Loading unsigned fastfile '{}', offset: {:#x}", name, offset);

	g_load.readOffset = offset;
	g_load.endOffset = offset + desiredReadBytes;

	int v16 = 4;
	do {
		hooking::invoke<int>(0x7FAA40, path, f, name); // test read?
		v16--;
	} while (v16);

	bool isSecure = false;
	int version = -1;

	auto header_error = hooking::invoke<const char*>(0x6C23D0, &isSecure, &version); // ValidateFileHeader
	if (header_error != nullptr) {
		spdlog::error("Error loading fastfile '{}': {}", name, header_error);
		return false;
	}
	else {
		spdlog::info("\tisSecure: {}, version: {:#x}", isSecure, version);
	}

	g_load.tail = 0;
	g_load.head = g_numStreams;

	return true;
}

bool db_load_xfile_stub(const char* path, int f, const char* name, game::XBlock* blocks, void (_cdecl* interrupt)(), uint8_t* buf, int allocType, int flags, int requiredVersion, unsigned int desiredReadBytes) {

	if (strstr(path, "winter") != nullptr) {
		is_loading_unsigned = true;
		spdlog::warn("Loading unsigned fastfile '{}'", name);
		//return load_unsigned_fastfile(path, f, name, blocks, interrupt, buf, allocType, flags, requiredVersion, desiredReadBytes);
	}
	else {
		spdlog::info("Loading fastfile '{}'", name);
	}

	bool result = db_load_xfile.invoke<bool>(path, f, name, blocks, interrupt, buf, allocType, flags, requiredVersion, desiredReadBytes);
	is_loading_unsigned = false;

	return result;
}

void db_load_xassets_stub(const game::XZoneInfo* zone, unsigned int zoneCount, int sync) {
	spdlog::info("Loading xassets for '{}', allocFlags: {:#x}, freeFlags: {:#x}, zoneCount: {:#x}, sync: {:#x}", zone->name, zone->allocFlags, zone->freeFlags, zoneCount, sync);
	db_load_xassets.invoke<void>(zone, zoneCount, sync);
}

void try_load_zone(const char* name) {
	strcpy_s(reinterpret_cast<char*>(0x12EED40), 64, name);
	hooking::invoke<void>(0x465110);
}

int com_init_ui_and_common_xassets_stub() {
	spdlog::info("Loading common and ui xassets");
	int res = com_init_ui_and_common_xassets.invoke<int>();
	try_load_zone("winter");

	// test
	auto testload = db_find_xasset_header_stub(game::ASSET_TYPE_RAWFILE, "ui_mp/t6/main.lua", 1, -1).rawfile;

	return res;
}

int ki_kore_load_hook(void* kore, void* state, void* a3, void* a4, char* name) {
	// basically lua_loadfile for compiled fastfile lua
	//spdlog::info("Lua: {}", name);
	int result = ki_kore_load.invoke<int>(kore, state, a3, a4, name);
	if (result == 0) {
		//spdlog::info("Lua loaded: {}", name);
	}
	else {
		//spdlog::error("Lua failed to load: {}", name);
	}
	return result;
}

int com_error_hook(int32_t error_type, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	spdlog::error("Error {}: {}", error_type, buffer);
	return 0;
}


BOOL WINAPI is_debugger_present_hook() {
	return FALSE;
}

int db_authload_init_stub(const uint8_t* buf, const char* name, char version, bool isSecure) {
	int ret = db_authload_init.invoke<int>(buf, name, version, isSecure);
	if (is_loading_unsigned) {
		spdlog::error("Skipping authload for fastfile '{}'", name);
		return 0;
	}
	spdlog::info("Authenticating fastfile '{}' -> {:#x}", name, ret);
	return ret;
}

int db_authload_getiv_stub(int a1, void* a2) {
	if (is_loading_unsigned) {
		memset(a2, 0, 8);
		return 0;
	}
	else {
		return db_authload_getiv.invoke<int>(a1, a2);
	}
}

int db_authload_analyzedata_stub(void *Src, int a2, void *a3, int a4, int a5, const uint8_t* iv, int a7) {
	if (is_loading_unsigned) {
		// skips salsa20 & sha1
		return 0;
	}
	
	return db_authload_analyzedata.invoke<int>(Src, a2, a3, a4, a5, iv, a7);
}

int inflate_stub(game::z_stream_s* zstream, int a2) {
	int ret = hooking::invoke<int>(0x5ACD80, zstream, a2);

	if (!is_loading_unsigned) {
		return ret;
	}

	if (zstream && zstream->msg) {
		spdlog::error("inflate error: {}", zstream->msg);
	}
	else {
		spdlog::info("inflate success");
	}

	return ret;
}

char* validate_file_header_stub(bool* isSecure, int* version) {
	auto ret = validate_file_header_hook.invoke<char*>(isSecure, version);
	if (ret && !strcmp("file not supported", ret)) {
		// TODO: actually handle unencrypted fastfiles
		return nullptr;
	}
	return ret;
}

int db_authload_add_checksum_stub(int a1, int a2) {
	if (is_loading_unsigned) {
		//++dword_1299374[v3]; // dword_1299374 -> int[5]
		*reinterpret_cast<int*>(0x1299374 + a1 * 4) += 1;
		return 0;
	}		
	return db_authload_add_checksum_hook.invoke<int>(a1, a2);
}

int db_authload_end_stub() {
	if (is_loading_unsigned) {
		spdlog::info("Skipping authload end");
		return 0;
	}
	return db_authload_add_checksum_hook.invoke<int>();
}

uint32_t db_reliable_fsopen_readonly_stub(const char* path_, uint32_t* outClumpSize) {
	std::string final_path;

	if (!util::file_exists(path_)) {
		std::string path = path_;
		std::string game_path = hooking::invoke<char*>(0x4233C0);
		// subtract game path from path
		auto pos = path.find(game_path);
		if (pos != std::string::npos) {
			path = path.substr(pos + game_path.length());
		}

		final_path = game_path + "\\winter" + path;
		path_ = final_path.c_str();
	}

	spdlog::info("Opening file '{}'", path_);

	return db_reliable_fsopen_readonly_hook.invoke<uint32_t>(path_, outClumpSize);
}

void patches::init() {
	memory::write<bool>(0x89925C, false); // ui_netsource 0
	memory::write<bool>(0x88A5AF, true); // xblive_rankedmatch 1
	memory::write<bool>(0x88A63F, true); // developer 1
	memory::write<bool>(0x88A657, true); // developer_script 1
	memory::write<bool>(0x88A3F7, false); // lui_checksum_enabled 0 
	memory::write<bool>(0x5664CA, false); // tu11_partymigrate_allowPrivatePartyClientsToHost 0
	memory::write<bool>(0x6B6607, true); // gpad_enabled 1

	// various patches that make offline mode work
	/*memory::write<int>(0x5BFA6B, 0xEB);
	memory::write<int>(0x5DDC20, 0xC3);
	memory::write<int>(0x544240, 0xC3);
	memory::write<int>(0xC1D910, 0x33);
	memory::write<int>(0xBE0F26, 0x33);
	memory::write<int>(0x4BE550, 0xC3);*/

	db_find_xasset_header.create(0x526800, &db_find_xasset_header_stub);
	//db_try_load_xfile_internal.create(xxx, &db_try_load_xfile_internal_stub);
	com_init_ui_and_common_xassets.create(0x4AF170, &com_init_ui_and_common_xassets_stub);
	db_load_xfile.create(0x4A6770, &db_load_xfile_stub);
	db_authload_init.create(0x667230, &db_authload_init_stub);
	//hooking::call(0x5476F3, &inflate_stub); // inflate
	//db_authload_getiv.create(0x55FFC0, &db_authload_getiv_stub);
	db_authload_analyzedata.create(0x495370, &db_authload_analyzedata_stub);
	validate_file_header_hook.create(0x6C23D0, &validate_file_header_stub);
	hooking::nop(0x6C1C89, 5); // nop DB_AuthLoad_End
	db_reliable_fsopen_readonly_hook.create(0x41F3E0, &db_reliable_fsopen_readonly_stub);
	db_load_xassets.create(0x58E8A0, &db_load_xassets_stub);

	auto kernel32 = GetModuleHandleA("kernel32.dll");
	if (kernel32 == NULL) {
		spdlog::warn("kernel32.dll not found, anti-debugger may not work");
	}
	else {
		hooking::qdetour(GetProcAddress(kernel32, "IsDebuggerPresent"), &is_debugger_present_hook);
	}


	spdlog::info("Patches initialized!");
}