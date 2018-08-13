#include "pch.h"
#include "BarData.h"

using namespace std;
using namespace DanceDanceAutomation;

BarData::BarData(const vector<TimeStamp>& beatTimings, float_t bpm, const TimeStamp& totalSongTime)
{
	float_t totalSongTimeMilliseconds = TimeStamp::TimeStampToMilliseconds(totalSongTime);
	float_t millisecondsEachBar = 2 * (4.0f * 60.0f * 1000.0f / bpm);
	float_t startTimeMilliseconds = TimeStamp::TimeStampToMilliseconds(beatTimings[0]);

	float_t timeTracker = startTimeMilliseconds;
	size_t i = 0;
	mBars.push_back(Bar());
	for (auto& beat : beatTimings)
	{
		bool done = false;
		while (!done)
		{
			if (TimeStamp::TimeStampToMilliseconds(beat) >= (timeTracker + millisecondsEachBar))
			{
				mBars[i].BarStartTimeMilliseconds = timeTracker;
				mBars[i].BarEndTimeMilliseconds = (timeTracker + (millisecondsEachBar));
				timeTracker += millisecondsEachBar;
				mBars.push_back(Bar());
				++i;
			}
			else
			{
				done = true;
			}
		}
		mBars[i].Bars.push_back(beat);



	}
	mBars[i].BarStartTimeMilliseconds = timeTracker;
	mBars[i].BarEndTimeMilliseconds = (totalSongTimeMilliseconds < (timeTracker + millisecondsEachBar)) ? totalSongTimeMilliseconds : (timeTracker + millisecondsEachBar);

}


const std::vector<Bar>& BarData::GetBars() const
{
	return mBars;
}