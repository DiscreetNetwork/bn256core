extern "C" {
#include "gfp_generic.h"
#include "export.h"
}

#ifdef _MSC_VER

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

BOOL APIENTRY DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }

    hasbmi2();

    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

#elif defined(__GNUC__)

#pragma init InitLib
void InitLib();

void InitLib() {
    hasbmi2();
}

#endif