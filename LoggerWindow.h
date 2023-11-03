#pragma once
#include "BaseWindow.h"
#include <fstream>

class LoggerWindow : public BaseWindow
{
public:
	LoggerWindow()
	{
		ofStream = std::ofstream(".\\LogResult.txt");
		hasFileOpened = ofStream.is_open();
	}

	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	LPCWSTR WndClassname() override;

	~LoggerWindow()
	{
		if (hasFileOpened)
			ofStream.close();
	}

private:
	std::ofstream ofStream;
	bool hasFileOpened = false;
};