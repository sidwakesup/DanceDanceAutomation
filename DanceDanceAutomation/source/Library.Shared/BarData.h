#pragma once

#include "TimeStamp.h"

namespace DanceDanceAutomation
{

	struct Bar
	{
		std::vector<TimeStamp> Bars;
		std::float_t BarStartTimeMilliseconds;
		std::float_t BarEndTimeMilliseconds;
	};

	class BarDifferenceFunction
	{
	public:
		std::float_t operator()(const Bar& bar1, const Bar& bar2)
		{
			std::float_t sum = 0.0f;
			if (bar1.Bars.size() != bar2.Bars.size())
			{
				sum = std::numeric_limits<float_t>::max();
			}
			else
			{
				if (bar1.Bars.size() != 0)
				{
					for (std::size_t i = 0; i < bar1.Bars.size(); ++i)
					{
						sum += abs((TimeStamp::TimeStampToMilliseconds(bar1.Bars[i]) - bar1.BarStartTimeMilliseconds) - (TimeStamp::TimeStampToMilliseconds(bar2.Bars[i]) - bar2.BarStartTimeMilliseconds));
					}
					sum /= static_cast<std::float_t>(bar2.Bars.size());
				}
			}

			return sum;
		}
	};

	class BarData
	{
	public:
		BarData(const std::vector<TimeStamp>& beatTimings, std::float_t bpm, const TimeStamp& totalSongTime);
		BarData(const BarData& other) = default;
		BarData(BarData&& other) = default;
		BarData& operator=(const BarData& other) = default;
		BarData& operator=(BarData&& other) = default;
		~BarData() = default;

		const std::vector<Bar>& GetBars() const;

	private:
		std::vector<Bar> mBars;
	};

}