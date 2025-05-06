#include <windows.h>
#include <iostream>

// thanks mr gpt.

bool InjectDLL(HANDLE hProcess, const char* dllPath) {
    size_t dllPathLen = strlen(dllPath) + 1;

    // Allocate memory in the remote process for the DLL path
    LPVOID remoteMemory = VirtualAllocEx(hProcess, nullptr, dllPathLen, MEM_COMMIT, PAGE_READWRITE);
    if (!remoteMemory) return false;

    // Write the DLL path to the remote process
    if (!WriteProcessMemory(hProcess, remoteMemory, dllPath, dllPathLen, nullptr)) return false;

    // Get address of LoadLibraryA
    LPTHREAD_START_ROUTINE loadLibraryAddr = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    if (!loadLibraryAddr) return false;

    // Create remote thread to call LoadLibraryA with our DLL path
    HANDLE remoteThread = CreateRemoteThread(hProcess, nullptr, 0, loadLibraryAddr, remoteMemory, 0, nullptr);
    if (!remoteThread) return false;

    // Wait for the DLL to be loaded
    WaitForSingleObject(remoteThread, INFINITE);

    // Clean up
    VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
    CloseHandle(remoteThread);
    return true;
}

int main() {
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    const char* exeName = "t6mp.exe";
    const char* dllName = "winter.dll";

    // Create the process in suspended state
    if (!CreateProcessA(nullptr, (LPSTR)exeName, nullptr, nullptr, FALSE,
        CREATE_SUSPENDED, nullptr, nullptr, &si, &pi)) {
		MessageBox(nullptr, L"Failed to start the game! (Process creation failed)", L"Error", MB_OK | MB_ICONERROR);
		std::cerr << "Failed to start the game! (Process creation failed)" << std::endl;
		return 1;
    }

    // Inject the DLL
    if (!InjectDLL(pi.hProcess, dllName)) {
		MessageBox(nullptr, L"Failed to inject winter library! (DLL injection failed)", L"Error", MB_OK | MB_ICONERROR);
		std::cerr << "Failed to inject winter library! (DLL injection failed)" << std::endl;
        return 1;
    }

    // Resume main thread of the process
    ResumeThread(pi.hThread);

    // Cleanup
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    std::cout << "Injected " << dllName << " into " << exeName << " successfully." << std::endl;
    return 0;
}
