#include "DX11Window.h"
int DX11Window::Height = 0;
int DX11Window::Width = 0;
void DX11Window::GetGameloopWindowRect()
{

	while (true)
	{
		RECT x;

		GetWindowRect(Game::hRenderWindow, &x);

		DX11Window::Height = x.bottom - x.top;
		DX11Window::Width = x.right - x.left;
		Sleep(100);
		if (Game::isUnloaded)
		{
			break;
		}
	}
}