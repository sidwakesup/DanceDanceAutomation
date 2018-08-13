#pragma once

#include "BarData.h"
#include "AmplitudeInfo.h"
#include "Defines.h"

namespace DanceDanceAutomation
{

	class StepChartGenerator
	{
	public:
		StepChartGenerator(const Waveform& waveform, std::float_t bpm, const BarData& barData, const std::vector<std::vector<std::size_t>>& cliques, const AmplitudeInfo& amplitudeInfo, const std::string& mp3FileName);
		StepChartGenerator(const StepChartGenerator& other) = default;
		StepChartGenerator(StepChartGenerator&& other) = default;
		StepChartGenerator& operator=(const StepChartGenerator& other) = default;
		StepChartGenerator& operator=(StepChartGenerator&& other) = default;
		~StepChartGenerator() = default;

		void FindMeasureTypesAndBeatLocations(const BarData& barData, const std::vector<std::vector<std::size_t>>& cliques);
		void GeneratePatterns(const Waveform& waveform, const BarData& barData, const std::vector<std::vector<std::size_t>>& cliques, const AmplitudeInfo& amplitudeInfo, 
			const std::map<const std::string, std::map<const std::string, std::size_t>>& TransitionProbabilities, const std::size_t AverageNumberOfPatternsPerMeasure, const std::float_t StandardDeviationDivider);
		std::size_t RandomNumberGenerator(std::size_t min, std::size_t max);
		void AddPatterns(std::fstream& stepFile);

	private:

		std::vector<std::vector<std::string>> mPatterns;
		std::vector<std::vector<std::string>> mCliquePatterns;
		std::vector<std::vector<std::size_t>> mCliqueMeasureBeatLocations;
		std::vector<bool> mCliqueMeasureTypes;

		std::float_t mTimeMillisecondsThirtySecondOfABar;
		std::float_t mTimeMillisecondsTwentyFourthOfABar;

		static const std::float_t ErrorTolerance;
	};

}