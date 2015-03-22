#pragma once

class CUTILTime {

public:
	CUTILTime();
	~CUTILTime();

	int GetCurrentYear();
	int GetCurrentMonth();
	int GetCurrentDay();
	int GetCurrentHour();
	int GetCurrentMinute();
	int GetCurrentSecond();
	
	void GetStringCurrentTime(CString &strtime);
	int CheckExpireSecond(int prevTime);

};

