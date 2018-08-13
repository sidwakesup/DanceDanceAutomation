#include "pch.h"
#include "AmplitudeInfo.h"

using namespace std;
using namespace DanceDanceAutomation;

AmplitudeInfo::AmplitudeInfo(const Waveform& waveform, const BarData& barData, const vector<vector<size_t>>& cliques) :
	mAverageAmplitude(0.0f), mMaxAmplitude(numeric_limits<uint16_t>::min()), mMinAmplitude(numeric_limits<uint16_t>::max())
{
	auto& sampleData = waveform.GetData();
	auto sampleDataSize = sampleData.size();

	auto& bars = barData.GetBars();

	if (sampleDataSize <= 0)
	{
		throw exception("Invalid waveform.");
	}

	mAverageAmplitudesPerBar.resize(barData.GetBars().size());
	mAverageAmplitudesPerClique.resize(cliques.size());

	size_t barCount = 0;
	size_t samplesInBar = 0;

	auto startSample = MillisecondsToSampleNumber(waveform.GetSampleRate(), bars[0].BarStartTimeMilliseconds);
	auto endSample = ((MillisecondsToSampleNumber(waveform.GetSampleRate(), bars.back().BarEndTimeMilliseconds) < sampleDataSize) ? MillisecondsToSampleNumber(waveform.GetSampleRate(), bars.back().BarEndTimeMilliseconds) : sampleDataSize);

	double_t amplitudeSum = accumulate(sampleData.begin() + startSample, sampleData.begin() + endSample, 0.0);
	mAverageAmplitude = static_cast<float_t>(amplitudeSum / (endSample - startSample + 1));
	double_t amplitudeSquareSum = 0.0;
	auto& mean = mAverageAmplitude;

	for_each(sampleData.begin() + startSample, sampleData.begin() + endSample, [&amplitudeSquareSum, &mean](const double_t d) { amplitudeSquareSum += (d - mean) * (d - mean); });
	mStandardDeviation = sqrt(amplitudeSquareSum / (endSample - startSample + 1));

	for (size_t i = startSample; i < endSample; ++i)
	{
		mMaxAmplitude = (sampleData[i] > mMaxAmplitude) ? sampleData[i] : mMaxAmplitude;
		mMinAmplitude = (sampleData[i] < mMinAmplitude) ? sampleData[i] : mMinAmplitude;

		if (i < ((MillisecondsToSampleNumber(waveform.GetSampleRate(), bars[barCount].BarEndTimeMilliseconds) < sampleDataSize) ? MillisecondsToSampleNumber(waveform.GetSampleRate(), bars[barCount].BarEndTimeMilliseconds) : sampleDataSize))
		{
			mAverageAmplitudesPerBar[barCount] += sampleData[i];
			++samplesInBar;
		}
		else
		{
			mAverageAmplitudesPerBar[barCount] /= static_cast<float_t>(samplesInBar);
			samplesInBar = 0;
			++barCount;
		}
	}
	mAverageAmplitudesPerBar[barCount] /= static_cast<float_t>(samplesInBar);

	size_t cliqueCount = 0;

	for (auto& clique : cliques)
	{
		for (size_t j = 0; j < clique.size(); ++j)
		{
			mAverageAmplitudesPerClique.at(cliqueCount) += mAverageAmplitudesPerBar.at((size_t)clique.at(j) - 1);
		}
		mAverageAmplitudesPerClique[cliqueCount] /= clique.size();
		++cliqueCount;
	}
}


size_t AmplitudeInfo::MillisecondsToSampleNumber(uint32_t sampleRate, float_t milliseconds) const
{
	return static_cast<size_t>((milliseconds / 1000) * sampleRate);
}