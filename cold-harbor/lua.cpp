#include "lua.h"
#include "logging.h"
#include "hooking.h"
#include <Windows.h>
#include "util.h"
#include "game.h"

HMODULE libhksc_dll = NULL;

hooking::detour lua_cod_getrawfile;
hooking::detour hks_compiler;

bool is_loading_raw_lua = false;

template<typename T, typename... Args>
T hksc_invoke(const char* export_name, Args... args) {
	auto func = GetProcAddress(libhksc_dll, export_name);
	if (!func) {
		util::fatal_error("Failed to get address of hksc function '%s'", export_name);
		return T();
	}
	return reinterpret_cast<T(*)(Args...)>(func)(args...);
}

game::XAssetHeader lua_cod_getrawfile_stub(const char* name) {
	auto ret = lua_cod_getrawfile.invoke<game::XAssetHeader>(name);
	if (!ret.rawfile) {
		return ret;
	}

	auto file = ret.rawfile->Buffer;
	if (file[0] != 0x1B && file[1] != 0x4C && file[2] != 0x75 && file[3] != 0x61 && file[4] != 0x51) {
		is_loading_raw_lua = true;
		spdlog::info("Loading raw lua file '{}'", name);
	}
	return ret;
}

int hksc_write(void* H, const void* p, size_t size, std::string* out) {
	out->append(static_cast<const char*>(p), size);
	return 0;
}

int hksc_dumper(void* H, void* ud) {
	hksc_invoke<int>("lua_dump", H, hksc_write, ud);
	return 0;
}

void compile_lua(const char* name, const char* buffer, size_t size, game::XAssetHeader* out_header) {
	lua::hksc_StateSettings settings;
	lua::hksc_State* H;

	hksc_invoke<void>("hksI_settings", &settings);
	H = hksc_invoke<lua::hksc_State*>("hksI_newstate", &settings);
	if (!H) {
		util::fatal_error("Failed to create hksc state");
	}

	hksc_invoke<void>("lua_setstrip", H, 2);

	std::string output_buffer;
	int ret = hksc_invoke<int>("hksI_parser_buffer", H, buffer, size, name, hksc_dumper, &output_buffer);
	if (ret != 0) {
		util::fatal_error("Failed to compile lua file '%s'", name);
	}
	else {
		spdlog::info("Compiled lua file '{}'", name);
	}

	out_header->rawfile = new game::RawFile;
	out_header->rawfile->Buffer = new char[output_buffer.size()];
	memcpy((void*)out_header->rawfile->Buffer, output_buffer.data(), output_buffer.size());
	out_header->rawfile->Length = output_buffer.size();
	out_header->rawfile->Name = name;
}

uint32_t hks_compiler_stub(void* state, void* a2, void* a3, game::XAssetHeader header, void* a5, void* a6, void* a7) {

	if (is_loading_raw_lua) {
		is_loading_raw_lua = false;
		game::XAssetHeader compiled_header{};
		compile_lua(header.rawfile->Name, header.rawfile->Buffer, header.rawfile->Length, &compiled_header);
		return hks_compiler.invoke<uint32_t>(state, a2, a3, compiled_header, a5, a6, a7);
	}

	return hks_compiler.invoke<uint32_t>(state, a2, a3, header, a5, a6, a7);
}

void lua::init() {
	if (libhksc_dll = LoadLibrary("winter/libhksc.dll")) {
		spdlog::info("libhksc loaded");
	}
	else {
		util::fatal_error("Failed to load libhksc.dll");
	}

	spdlog::info("libhksc initialized");

	lua_cod_getrawfile.create(0x494BA0, &lua_cod_getrawfile_stub);
	hks_compiler.create(0x468510, &hks_compiler_stub);
}