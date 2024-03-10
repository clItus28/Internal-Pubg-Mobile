#include "Includes.h"

#include "Data.h"
using namespace KeyAuth;
std::string name = XorStr("Bypass");
std::string ownerid = XorStr("Y5fxkIGb1G");
std::string secret = XorStr("8872653d314f3b3a7e787682834985086065787b5b2c9533cc46dce8e4b5310a");
std::string version = XorStr("1.4");

api KeyAuthApp(name, ownerid, secret, version);

BYTE Present1Bytes[] = { 0x8B, 0xFF, 0x55, 0x8B, '?', '?', '?', '?','?' , '?', '?', 0xA1, '?', '?', '?', '?', 0x33, 0xC4, 0x89, 0x44, 0x24, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x39, 0x73, 0x08 };
BYTE Present1Bytes2[] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x83, 0xE4, 0xF8, 0x81, 0xEC, 0xDC, 0x00, 0x00, 0x00, 0xA1, '?', '?', '?', '?', '?', '?', '?', '?', '?', 0xD8, 0x00, 0x00, 0x00, 0x53, 0x8B, 0x5D, 0x14, 0x33, 0xC9, 0x56, 0x57, 0x8B, 0x7D, 0x08, 0x8B, 0x53, 0x08, 0x89, 0x4C, 0x24, 0x0C, 0x85, 0xD2 };
BYTE UE4Byte[] = { 0x06, 0x00, 0x12, 0xE3, 0x08, 0x10, 0x90, 0xE5, 0x88, 0x70, 0x91, 0xE5, 0x68, 0x30, 0x91, 0xE5, 0x06, 0xE1, 0x87, 0xE0, 0x06, 0x42, 0x83, 0xE0, 0x05, 0x60, 0xA0, 0xE3, 0x0E, 0x30, 0xA0, 0xE1, 0x04, 0x60, 0x00, 0x13, 0x04, 0x50, 0xB3, 0xE5, 0x08, 0x20, 0x9C, 0xE5, 0x20, 0x70, 0x94, 0xE5 };
vector<DWORD_PTR> FoundedPresent1;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    char Buffer[1000];
    GetClassNameA(hWnd, Buffer, 1000);

    string WindowClassName = Buffer;

    if (WindowClassName.find("TXGuiFoundation") != string::npos)
    {
        wchar_t Name[1000];
        GetWindowTextW(hWnd, Name, 1000);
        if (wcscmp(Name, L"TXMenuWindow") == 0)
        {
            return TRUE;
        }
        if (wcscmp(Name, L"") == 0)
        {
            return TRUE;
        }
        Game::hWindow = FindWindowW(L"TXGuiFoundation", Name);
    }

    return TRUE;
}

DWORD WINAPI MainThread(LPVOID lpThreadParameter)
{
    Game::EmuProcHandle = GetCurrentProcess();
    Game::DXGIPointer = (DWORD)GetModuleHandleA(("dxgi.dll"));
    Tools::MemSearchEmulator(Present1Bytes, sizeof(Present1Bytes), Game::DXGIPointer, Game::DXGIPointer + 0xFFFFF, false, 0, FoundedPresent1);
    if (FoundedPresent1.size() == 1 && FoundedPresent1.size() != 0)
    {
        Game::DXGIPresent1 = FoundedPresent1[0];
    }
    else
    {
        Tools::MemSearchEmulator(Present1Bytes2, sizeof(Present1Bytes2), Game::DXGIPointer, Game::DXGIPointer + 0xFFFFF, false, 0, FoundedPresent1);
        if (FoundedPresent1.size() == 1 && FoundedPresent1.size() != 0)
        {
            Game::DXGIPresent1 = FoundedPresent1[0];
        }
        else
        {
            //REPEAT SAME UNTIL FOUND PRESENT1 PATTERN OF ALL PC :)
        }
    }
    EnumWindows(EnumWindowsProc, 0);
    Game::hRenderWindow = FindWindowExW(Game::hWindow, 0, L"AEngineRenderWindowClass", L"AEngineRenderWindow");
 
    Game::GamePID = Tools::GetTrueProcessId((PCHAR)"aow_exe.exe");
    Tools::GameProcess = OpenProcess(PROCESS_ALL_ACCESS, false, Game::GamePID);
    Data::Ue4base = Data::GetUe4Base(0x25000000, 0x60000000);
    Data::ViewMatrixBase = Data::GetViewMatrixBase(0x50000000, 0x70000000);
    //MessageBox(0, to_string(Data::ViewMatrixBase).c_str(), 0, 0);
    Hook::Init();

    return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Game::CurrentModule = hModule;
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DX11Window::GetGameloopWindowRect, 0, 0, 0);
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
        
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

