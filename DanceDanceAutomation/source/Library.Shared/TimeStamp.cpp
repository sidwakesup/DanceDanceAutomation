#include "pch.h"
#include "TimeStamp.h"

using namespace DanceDanceAutomation;

TimeStamp::TimeStamp()
{
	minutes = 0;
	seconds = 0;
	milliseconds = 0;
	metaData = (char*)"";
}

TimeStamp::~TimeStamp()
{
	delete metaData;
}

TimeStamp::TimeStamp(int m ,int s,int mil)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	metaData = (char*)"";
}

TimeStamp::TimeStamp(int m, int s, int mil, float f)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	beatFrequency = f;
}

TimeStamp::TimeStamp(int m, int s, int mil, char* md)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	metaData = md;
}

void TimeStamp::setTime(int m, int s, int mil)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
}

void TimeStamp::setMinutes(int m)
{
	minutes = m;
}

void TimeStamp::setSeconds(int s)
{
	seconds = s;
}

void TimeStamp::setMilliseconds(int mil)
{
	milliseconds = mil;
}

void TimeStamp::setFrequency(float f)
{
	beatFrequency = f;
}

void TimeStamp::setTimeWithMetaData(int m, int s, int mil, char* md)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	metaData = md;
}

void TimeStamp::setTimeWithFrequency(int m, int s, int mil, float f)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	beatFrequency = f;
}


int TimeStamp::getMinutes() const
{
	return minutes;
}

int TimeStamp::getSeconds() const
{
	return seconds;
}

int TimeStamp::getMilliseconds() const
{
	return milliseconds;
}

float TimeStamp::getFrequency() const
{
	return beatFrequency;
}

char* TimeStamp::getMetaData() const
{
	return metaData;
}



float_t TimeStamp::TimeStampToMilliseconds(const TimeStamp& timeStamp)
{
	int32_t minutes = timeStamp.getMinutes();
	int32_t seconds = timeStamp.getSeconds();
	int32_t milliseconds = timeStamp.getMilliseconds();

	return static_cast<float>((minutes * 60 * 1000) + (seconds * 1000) + (milliseconds));
}