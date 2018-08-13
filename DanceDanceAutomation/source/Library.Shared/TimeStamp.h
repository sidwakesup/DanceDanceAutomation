#pragma once

namespace DanceDanceAutomation
{

	class TimeStamp
	{
	public:
		TimeStamp();
		TimeStamp(int, int, int);
		TimeStamp(int, int, int, float);
		TimeStamp(int, int, int, char*);
		~TimeStamp();

		void setTime(int, int, int);
		void setSeconds(int);
		void setMinutes(int);
		void setMilliseconds(int);
		void setFrequency(float);

		int getSeconds() const;
		int getMinutes() const;
		int getMilliseconds() const;
		float getFrequency() const;
		char* getMetaData() const;

		static std::float_t TimeStampToMilliseconds(const TimeStamp& timeStamp);

		void setTimeWithMetaData(int, int, int, char*);
		void setTimeWithFrequency(int, int, int, float);
	private:
		int minutes;
		int seconds;
		int milliseconds;
		char* metaData;
		float beatFrequency;
	};

}