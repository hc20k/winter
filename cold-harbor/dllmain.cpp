// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "core.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
		// Disable thread library calls
		DisableThreadLibraryCalls(hModule);
		// Initialize the core
		core::setup();
		break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// fake export
void __declspec(dllexport) _dummy() {
	// This function is intentionally left empty.
	// It serves as a placeholder for the DLL export.
}
