#pragma once
#include <wtypes.h>
#include <tchar.h>
#include <vector>

#define ID_SUBMIT 1

#define MAIN_WINDOW_WIDTH 410
#define MAIN_WINDOW_HEIGHT 170

class ClockUI
{
public:
	void CreateLabels(HDC hdc);
	void CreateInputs(HWND hWnd);
	void CreateButton(HWND hWnd);

	std::vector <HWND> inputs;
};

