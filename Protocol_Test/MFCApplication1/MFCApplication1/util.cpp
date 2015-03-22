#include "stdafx.h"
#include "util.h"

CUTILTime::CUTILTime()
{
}

CUTILTime::~CUTILTime()
{
}

void CUTILTime::GetStringCurrentTime(CString &strTime)
{
	SYSTEMTIME m_curTime;

	GetLocalTime (&m_curTime);

	strTime.Format("%d/%d/%d - %d:%d:%d", m_curTime.wYear, m_curTime.wMonth, m_curTime.wDay,
		m_curTime.wHour, m_curTime.wMinute, m_curTime.wSecond);
}

int CUTILTime::GetCurrentYear()
{
	SYSTEMTIME m_curTime;
	GetLocalTime (&m_curTime);
	return m_curTime.wYear;
}
int CUTILTime::GetCurrentMonth()
{
	SYSTEMTIME m_curTime;
	GetLocalTime (&m_curTime);
	return m_curTime.wMonth;
}
int CUTILTime::GetCurrentDay()
{
	SYSTEMTIME m_curTime;
	GetLocalTime (&m_curTime);
	return m_curTime.wDay;
}
int CUTILTime::GetCurrentHour()
{
	SYSTEMTIME m_curTime;
	GetLocalTime (&m_curTime);
	return m_curTime.wHour;
}
int CUTILTime::GetCurrentMinute()
{
	SYSTEMTIME m_curTime;
	GetLocalTime (&m_curTime);
	return m_curTime.wMinute;
}

int CUTILTime::GetCurrentSecond()
{
	SYSTEMTIME m_curTime;
	GetLocalTime (&m_curTime);
	return m_curTime.wSecond;
}


int CUTILTime::CheckExpireSecond(int prevTime)
{
	SYSTEMTIME m_curTime;
	GetLocalTime (&m_curTime);

	if ( prevTime > m_curTime.wSecond)
	{
		return (prevTime - m_curTime.wSecond);
	}
	else{
		return (m_curTime.wSecond - prevTime);
	}
}

