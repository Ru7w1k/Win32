// Headers 
#include <windows.h>
#include "Square_MS.h"

// DllMain
BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	// code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

// Exported functions
extern "C" __declspec(dllexport) int MakeSquare(int iNum)
{
	return (iNum * iNum);
}

