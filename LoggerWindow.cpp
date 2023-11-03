#include "LoggerWindow.h"

LRESULT LoggerWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INPUT:
	{
		// сначала получаем в байткод rawinput data
		UINT required_size = 0U;
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &required_size, sizeof(RAWINPUTHEADER));
		BYTE* pByteCode = new BYTE[required_size];
		UINT bytes = GetRawInputData((HRAWINPUT)lParam, RID_INPUT, pByteCode, &required_size, sizeof(RAWINPUTHEADER));

		// интерпретируем как указатель на структуру RAWINPUT
		PRAWINPUT pRawInput = (PRAWINPUT)pByteCode;

		if (pRawInput->header.dwType == RIM_TYPEMOUSE)
		{
			POINT pt;
			GetCursorPos(&pt);

			if (pRawInput->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)
			{
				if (hasFileOpened)
					ofStream << "Mouse left button click at [ X = " << pt.x << " Y = " << pt.y << " ]" << std::endl;
			}

			if (pRawInput->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN)
			{
				if (hasFileOpened)
					ofStream << "Mouse right button click at [ X = " << pt.x << " Y = " << pt.y << " ]" << std::endl;
			}

			if (pRawInput->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN)
			{
				if (hasFileOpened)
					ofStream << "Mouse middle button click at [ X = " << pt.x << " Y = " << pt.y << " ]" << std::endl;
			}
		}

		if (pByteCode) delete[] pByteCode;
		break;
	}
	case WM_DESTROY:
		::PostQuitMessage(EXIT_SUCCESS);
		return 0;
	}

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LPCWSTR LoggerWindow::WndClassname()
{
    return L"LoggerWindowClassName";
}
