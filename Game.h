#pragma once
#include "Includes.h"
namespace Game
{
	extern DWORD DXGIPointer;
	extern DWORD DXGIPresent1;
	extern HMODULE CurrentModule;	
	extern HANDLE EmuProcHandle;
	extern DWORD GamePID;

	extern HWND hWindow;
	extern HWND hRenderWindow;
	extern bool isUnloaded;
}
