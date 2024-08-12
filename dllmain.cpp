#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	DisableThreadLibraryCalls(hModule);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		spoof_call(Initialize);
		return TRUE;

	case DLL_PROCESS_DETACH:
		spoof_call(Deallocate);
		return TRUE;
	}

	return FALSE;
}

