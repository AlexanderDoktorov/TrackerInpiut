#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>

void PrintResults() noexcept;

class Logger
{
public:
	Logger() = default;

	static void Run()
	{
		std::thread LoggingThread(PrintResults);
		InitMouseHook();
		BeginMessageLoop();
		LoggingThread.join();
	}

	static unsigned int GetClickCount() noexcept;

	static LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		if (nCode == HC_ACTION) {
			switch (wParam)
			{
			case WM_LBUTTONDOWN:
				clickCounter++;
				break;
			case WM_RBUTTONDOWN:
				clickCounter++;
				break;
			case WM_MBUTTONDOWN:
				UnhookWindowsHookEx(hmouseHook);
				PostQuitMessage(EXIT_SUCCESS);
				break;
			}
		}
		return CallNextHookEx(hmouseHook, nCode, wParam, lParam);
	}

	static void InitMouseHook()				noexcept
	{
		hmouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, nullptr, 0);

		if (hmouseHook == NULL) {
			MessageBox(NULL, L"Failed to set up mouse hook.", L"Error", MB_ICONERROR);
		}
	}
	static void BeginMessageLoop()			noexcept
	{
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

private:
	static HHOOK hmouseHook;
	static unsigned int clickCounter;
};