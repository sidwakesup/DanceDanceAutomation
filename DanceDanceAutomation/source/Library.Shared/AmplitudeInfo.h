#pragma once

#include "Waveform.h"
#include "BarData.h"

namespace DanceDanceAutomation
{

	class AmplitudeInfo
	{
	public:
		AmplitudeInfo(const Waveform& waveform, const BarData& barData, const std::vector<std::vector<std::size_t>>& cliques);
		AmplitudeInfo(const AmplitudeInfo& other) = default;
		AmplitudeInfo(AmplitudeInfo&& other) = default;
		AmplitudeInfo& operator=(const AmplitudeInfo& other) = default;
		AmplitudeInfo& operator=(AmplitudeInfo&& other) = default;
		~AmplitudeInfo() = default;

		inline std::float_t GetAverageAmplitude() const { return mAverageAmplitude; }
		inline std::uint16_t GetMaxAmplitude() const { return mMaxAmplitude; }
		inline std::uint16_t GetMinAmplitude() const { return mMinAmplitude; }
		inline const std::vector<std::float_t>& GetAverageAmplitudesPerBar() const { return mAverageAmplitudesPerBar; }
		inline const std::vector<std::float_t>& GetAverageAmplitudesPerClique() const { return mAverageAmplitudesPerClique; }
		inline std::double_t GetStandardDeviation() const { return mStandardDeviation; }

		std::size_t MillisecondsToSampleNumber(std::uint32_t sampleRate, std::float_t milliseconds) const;

	private:
		std::float_t mAverageAmplitude;
		std::uint16_t mMaxAmplitude;
		std::uint16_t mMinAmplitude;
		std::vector<std::float_t> mAverageAmplitudesPerBar;
		std::vector<std::float_t> mAverageAmplitudesPerClique;
		std::double_t mStandardDeviation;

	};

}