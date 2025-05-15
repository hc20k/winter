#include "gsc.h"
#include "hooking.h"
#include "game.h"
#include "logging.h"
#include "util.h"

hooking::detour load_script_parse_tree_asset;
HMODULE gsc_tool_dll = NULL;

template<typename T, typename... Args>
T gsc_tool_invoke(const char* export_name, Args... args) {
	auto func = GetProcAddress(gsc_tool_dll, export_name);
	if (!func) {
		util::fatal_error("Failed to get address of gsc-tool function '%s'", export_name);
		return T();
	}
	return reinterpret_cast<T(*)(Args...)>(func)(args...);
}

void* load_script_parse_tree_asset_stub(game::ScriptParseTree** tree_) {
	auto tree = *tree_;

	if (tree) {
		spdlog::info("Loading script parse tree asset '{}'", tree->name);

		if (*(uint64_t*)tree->buffer != 0x06000A0D43534780u) {
			gsc_tool_invoke<void>("winter_compile", tree->buffer, tree->len, NULL, NULL);
		}
	}

	return load_script_parse_tree_asset.invoke<void*>(tree_);
}


void gsc::init() {
	if (gsc_tool_dll = LoadLibrary("winter/gsc-tool.dll")) {
		spdlog::info("gsc-tool loaded");
	}
	else {
		util::fatal_error("Failed to load gsc-tool.dll");
	}
		
	if (!gsc_tool_invoke<bool>("winter_init")) {
		util::fatal_error("Failed to initialize gsc-tool");
	}	

	load_script_parse_tree_asset.create(0x5E7060, &load_script_parse_tree_asset_stub);
}