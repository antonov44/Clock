#pragma once

#include "ClockUI.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost::gregorian;
using namespace boost::posix_time;

#define MAX_BUF_SIZE	8
#define TIMER_ID		100

class ClockUtils
{
public:
	ClockUtils();
	void onSubmitHandler(HWND hWnd, ClockUI ui);
	void UpdateDatetime();
	std::stringstream& GetDatetime();
	void SetCurrentDatetime(ClockUI ui);
private:
	bool isTimerActive;
	date appdate;
	ptime apptime;
	int interval;
	std::stringstream datetimeString;
};

