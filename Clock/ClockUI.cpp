#include "ClockUI.h"

void ClockUI::CreateLabels(HDC hdc)
{
	const WCHAR* hstr[] = {
		_T("dd"),
		_T("mm"),
		_T("yyyy"),
		_T("h"),
		_T("m"),
		_T("s"),
		_T("ms"),
		_T("Interval")
	};

	const int offsetX = 10;
	const int offsetY = 10;

	const int marginsX[] = {
		0, 25, 52, 98, 121, 146, 175, 213
	};

	for (int i = 0; i < 8; i++)
	{
		TextOut(hdc, offsetX + marginsX[i], offsetY, hstr[i], _tcslen(hstr[i]));
	}
}

void ClockUI::CreateInputs(HWND hWnd)
{
	const WCHAR* hstr[] = {
		_T("0"),
		_T("00"),
		_T("0000")
	};

	const int widthS = 22;
	const int widthL = 38;
	const int height = 20;

	const int offsetX = 10;
	const int offsetY = 30;

	const int marginsX[] = {
		0, 25, 50, 91, 116, 141, 166, 207
	};

	HWND temp;

	for (int i = 0; i < 8; i++)
	{
		if (i == 2 || i == 6)
		{
			temp = CreateWindow(_T("EDIT"), hstr[2], WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, offsetX + marginsX[i], offsetY, widthL, height, hWnd, NULL, NULL, NULL);
			SendMessage(temp, EM_SETLIMITTEXT, 4, 0);
		}
		else if (i == 7)
		{
			temp = CreateWindow(_T("EDIT"), hstr[0], WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, offsetX + marginsX[i], offsetY, widthL + 25, height, hWnd, NULL, NULL, NULL);
			SendMessage(temp, EM_SETLIMITTEXT, 4, 0);
		}
		else
		{
			temp = CreateWindow(_T("EDIT"), hstr[1], WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER, offsetX + marginsX[i], offsetY, widthS, height, hWnd, NULL, NULL, NULL);
			SendMessage(temp, EM_SETLIMITTEXT, 2, 0);
		}

		inputs.push_back(temp);
	}
}

void ClockUI::CreateButton(HWND hWnd)
{
	const int offsetX = 283;
	const int offsetY = 30;
	const int width = 100;
	const int height = 20;

	CreateWindow(
		_T("BUTTON"), _T("Submit"), 
		WS_CHILD | WS_VISIBLE | BS_FLAT | BS_PUSHBUTTON, 
		offsetX, offsetY, width, height, 
		hWnd, 
		(HMENU)ID_SUBMIT, 
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
		NULL
	);
}
