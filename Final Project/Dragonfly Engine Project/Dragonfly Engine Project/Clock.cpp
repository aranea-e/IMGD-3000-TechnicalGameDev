#include <Windows.h>
#include "Clock.h"

df::Clock::Clock()
{
	SYSTEMTIME time;
	GetSystemTime(&time);
	m_previous_time = (time.wDay * 24 * 60 * 60 * 1000000)
					+ (time.wHour * 60 * 60 * 1000000)
					+ (time.wMinute * 60 * 1000000)
					+ (time.wSecond * 1000000)
					+ (time.wMilliseconds * 1000);
}

long long df::Clock::delta()
{
	SYSTEMTIME time;
	long long out_time, new_time;
	GetSystemTime(&time);
	new_time = (time.wDay * 24 * 60 * 60 * 1000000)
		+ (time.wHour * 60 * 60 * 1000000)
		+ (time.wMinute * 60 * 1000000)
		+ (time.wSecond * 1000000)
		+ (time.wMilliseconds * 1000);
	out_time = new_time - m_previous_time;
	m_previous_time = new_time;
	return out_time;
}

long long df::Clock::split() const
{
	SYSTEMTIME time;
	long long out_time, new_time;
	GetSystemTime(&time);
	new_time = (time.wDay * 24 * 60 * 60 * 1000000)
		+ (time.wHour * 60 * 60 * 1000000)
		+ (time.wMinute * 60 * 1000000)
		+ (time.wSecond * 1000000)
		+ (time.wMilliseconds * 1000);
	out_time = new_time - m_previous_time;
	return out_time;
}
