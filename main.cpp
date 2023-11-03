#include <windows.h>
#include <hidusage.h>
#include "LoggerWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	LoggerWindow loggerWnd;
	loggerWnd.Create(L"Logger Window", WS_OVERLAPPEDWINDOW);
	loggerWnd.Show(nShowCmd);

	RAWINPUTDEVICE rawInputMouseDevice[1];
	rawInputMouseDevice[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	rawInputMouseDevice[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	rawInputMouseDevice[0].hwndTarget = loggerWnd.GetWindow();
	rawInputMouseDevice[0].dwFlags = 0;

	if (!RegisterRawInputDevices(rawInputMouseDevice, ARRAYSIZE(rawInputMouseDevice), sizeof(RAWINPUTDEVICE)))
	{
		MessageBox(NULL, L"Unable to register raw input devices", L"ERROR", MB_OK | MB_ICONERROR);
			return -1;
	}

	MSG msg{};
	while(int bRet = GetMessage( &msg, NULL, 0, 0 ))
	{ 
		if (bRet == -1)
		{
			break;
		}
		else
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}

	return (int)msg.wParam;
}