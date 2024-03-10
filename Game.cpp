#include "Includes.h"

DWORD Game::DXGIPointer = 0;
DWORD Game::DXGIPresent1 = 0;

HMODULE Game::CurrentModule = 0;
HANDLE Game::EmuProcHandle = 0;
DWORD Game::GamePID = 0;

HWND Game::hWindow = 0;
HWND Game::hRenderWindow = 0;
bool Game::isUnloaded = 0;