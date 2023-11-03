#pragma once
#include <Windows.h>

class BaseWindow
{
public:

	BaseWindow() = default;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		BaseWindow* pThis = nullptr;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreateStruct = (CREATESTRUCT*)lParam;
			pThis = static_cast<BaseWindow*>(pCreateStruct->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->hwnd = hwnd;
		}
		else
		{
			pThis = (BaseWindow*)(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}

		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	bool Create( 
		LPCWSTR lpWindowName,
		DWORD dwStyle,
		int X = 0,
		int Y = 0,
		int nWidth = 500,
		int nHeight = 500,
		HWND hWndParent = (HWND)0,
		HMENU hMenu = (HMENU)0)
	{
		WNDCLASSEXW wc{};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpfnWndProc = WndProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = WndClassname();

		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, L"Unable to register window class", L"ERROR", MB_OK | MB_ICONERROR);
			return false;
		}

		hwnd = CreateWindowW(WndClassname(), lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, wc.hInstance, this);

		if (!hwnd)
		{
			MessageBox(NULL, L"Unable to create window", L"ERROR", MB_OK | MB_ICONERROR);
			return false;
		}

		return true;
	}

	void Show(int nShowCmd = SW_NORMAL)
	{
		ShowWindow(hwnd, nShowCmd);
		UpdateWindow(hwnd); 
	}

	HWND GetWindow() const noexcept
	{
		return hwnd;
	}
	
	virtual LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	virtual LPCWSTR WndClassname() = 0;

protected:
	HWND hwnd = NULL;
};