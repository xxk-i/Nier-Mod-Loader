#include "stdafx.h"
#include "Memory.h"
#include "Windows.h"
#include <string>

using std::string;

void MainLoop()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_END))
		{
			uintptr_t modBase = (uintptr_t)GetModuleHandle(NULL);
			typedef int(__fastcall * _loadCPK)(__int64 *id);
			_loadCPK loadCPK;
			loadCPK = (_loadCPK)(modBase + 0x644000);

			string *cpkIDptr = new string;
			string cpkID = "\\mods\\coolmod";	//.cpk stripped from name, (custom.cpk)

			*(string*)cpkIDptr = cpkID;
			loadCPK((__int64*)&cpkIDptr);
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, 0, (unsigned long(__stdcall*)(void*))MainLoop, NULL, 0, NULL);
	}
	return TRUE;
}