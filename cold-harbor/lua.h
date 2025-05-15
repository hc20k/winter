#pragma once
#define LUA_API		extern

namespace lua
{
	typedef struct hksc_State hksc_State;
	typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);
	typedef int (*lua_CFunction) (hksc_State *H);

	typedef struct {
		int hash_step;		/* general settings */
		int ignore_debug; /* do not try to load/dump debug info */
		/* compiler-specific settings */
		int emit_struct; /* whether `hstructure' and `hmake' should be emitted */
		int literals; /* int literal setting */
		int strip; /* bytecode stripping level */
		/*const char **strip_names;*/
		/*lua_LineMap debug_map;*/
		int match_line_info; /* emit statements according to the line mapping */
	} hksc_CompilerSettings;

	typedef struct {
		lua_Alloc frealloc;  /* function to reallocate memory */
		void *ud;         /* auxiliary data to `frealloc' */
		lua_CFunction panic;  /* to be called in unprotected errors */
		int mode;  /* what mode to run in (compiling/decompiling) */
		int bytecode_endianness;
		hksc_CompilerSettings compilersettings;
	} hksc_StateSettings;



	void init();
};

