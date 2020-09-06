#include "ClockUtils.h"

ClockUtils::ClockUtils()
{
	isTimerActive = false;
	interval = 0;
	datetimeString << "00.00.0000 00:00:00:000";
}

void ClockUtils::onSubmitHandler(HWND hWnd, ClockUI ui)
{
	bool isValidated = false;

	std::vector <int> inputResults;
	
	WCHAR buf[MAX_BUF_SIZE];
	
	for (auto input : ui.inputs)
	{
		GetWindowText(input, buf, MAX_BUF_SIZE);
		inputResults.push_back(_wtoi(buf));
	}

	try
	{
		// Here we try to create special variables that hold datetime.
		// If we did - success! Switch isValidated flag to true and return the result.
		// If not - we show a message box with an error.
		date dateInit(inputResults[2], inputResults[1], inputResults[0]);
		ptime timeInit(
			dateInit,
			hours(inputResults[3]) + minutes(inputResults[4]) + seconds(inputResults[5]) + millisec(inputResults[6])
		);

		appdate = dateInit;
		apptime = timeInit;

		isValidated = true;
	}
	catch (const std::exception& e)
	{
		MessageBoxA(hWnd, e.what(), "Error!", MB_ICONWARNING | MB_OKCANCEL);
		return;
	}

	interval = inputResults[7];

	try
	{
		if (interval < 1000)
			throw std::exception("Invalid interval. (Interval >= 1000).");
	}
	catch (const std::exception& e)
	{
		MessageBoxA(hWnd, e.what(), "Error!", MB_ICONWARNING | MB_OKCANCEL);
		return;
	}

	if (isValidated == true)
	{
		if (isTimerActive == true)
			KillTimer(hWnd, TIMER_ID);

		SetTimer(hWnd, TIMER_ID, interval, 0);
		isTimerActive = true;
	}
}

void ClockUtils::UpdateDatetime()
{
	int day, month, year;
	int hours, minutes, seconds, milliseconds;

	apptime += millisec(interval);
	appdate = apptime.date();

	time_duration datetime = apptime.time_of_day();

	day = appdate.day();
	month = appdate.month();
	year = appdate.year();

	hours = datetime.hours();
	minutes = datetime.minutes();
	seconds = datetime.seconds();
	milliseconds = datetime.total_milliseconds() - datetime.total_seconds() * 1000;

	std::string time = to_simple_string(datetime);

	datetimeString.str(std::string());
	datetimeString << (day < 10 ? "0" : "") << day << "." << (month < 10 ? "0" : "") << month << "." << year << " " << (hours < 10 ? "0" : "") << hours << ":" << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << ":" << (milliseconds < 10 ? "0" : "") << (milliseconds < 100 ? "0" : "") << milliseconds;
}

std::stringstream& ClockUtils::GetDatetime()
{
	return datetimeString;
}

void ClockUtils::SetCurrentDatetime(ClockUI ui)
{
	char BUF[MAX_BUF_SIZE];
	std::vector <int> datetime;

	SYSTEMTIME systime;
	GetLocalTime(&systime);

	ptime now = second_clock::local_time();

	date currentDate = now.date();
	time_duration currentTime = now.time_of_day();

	datetime.push_back(currentDate.day());
	datetime.push_back(currentDate.month());
	datetime.push_back(currentDate.year());

	datetime.push_back(currentTime.hours());
	datetime.push_back(currentTime.minutes());
	datetime.push_back(currentTime.seconds());

	datetime.push_back(systime.wMilliseconds);

	for (int i = 0; i < 7; i++)
	{
		_itoa_s(datetime[i], BUF, sizeof(BUF), 10);
		SetWindowTextA(ui.inputs[i], BUF);
	}
}


