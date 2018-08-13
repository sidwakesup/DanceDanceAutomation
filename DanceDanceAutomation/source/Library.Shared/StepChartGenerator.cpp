#include "pch.h"
#include "StepChartGenerator.h"
#include <random>


using namespace std;
using namespace DanceDanceAutomation;

const float_t StepChartGenerator::ErrorTolerance = 20.0f;

StepChartGenerator::StepChartGenerator(const Waveform& waveform, float_t bpm, const BarData& barData, const vector<vector<size_t>>& cliques, const AmplitudeInfo& amplitudeInfo, const string& mp3FileName)
{
	mTimeMillisecondsThirtySecondOfABar = 2 * (4.0f * 60.0f * 1000.0f) / (bpm * 32.0f);
	mTimeMillisecondsTwentyFourthOfABar = 2 * (4.0f * 60.0f * 1000.0f) / (bpm * 24.0f);

	FindMeasureTypesAndBeatLocations(barData, cliques);

	string simFileName;
	string songName;
	size_t found1 = mp3FileName.rfind("\\");
	if (found1 != string::npos)
	{
		simFileName = mp3FileName.substr(0, found1);
	}
	size_t found2 = mp3FileName.rfind(".mp3");
	songName = mp3FileName.substr((found1 + 1), (found2 - (found1 + 1)));
	simFileName += "\\" + songName + ".sm";

	fstream stepFile(simFileName, ios_base::out);
	string info1("#TITLE:" + songName + ";\n#SUBTITLE:;\n#ARTIST:DanceDanceAutomation;\n");
	string info2("#TITLETRANSLIT:;\n#SUBTITLETRANSLIT:;\n#ARTISTTRANSLIT:;\n#CREDIT:;\n");
	string info3("#BANNER:;\n#BACKGROUND:;\n#CDTITLE:SiddhantRavi;\n#MUSIC:" + songName + ".mp3;\n");
	float_t offset = -((barData.GetBars().at(0).BarStartTimeMilliseconds + 65) / 1000.0f);
	string info4("#OFFSET:" + to_string(offset) + ";\n#SAMPLESTART:0.000000;\n#SAMPLELENGTH:5.000000;\n");
	string info5("#BPMS:0.000000=" + to_string(bpm / 2) + ";\n#STOPS:;\n#BGCHANGE:;\n");
	stepFile << info1 << info2 << info3 << info4 << info5;

	//beginner
	string info6("#NOTES:\n\tdance-single:\n\tDanceDanceAutomation:\n\tbeginner:\n\t1:\n\t0.000,0.000,0.000,0.000,0.000:\n");
	stepFile << info6;
	GeneratePatterns(waveform, barData, cliques, amplitudeInfo, BeginnerTransitionProbabilities, Beginner_AverageNumberOfPatternsPerMeasure, Beginner_StandardDeviationDivider);
	AddPatterns(stepFile);
	mCliquePatterns.clear();
	mPatterns.clear();

	//easy
	info6 = "#NOTES:\n\tdance-single:\n\tDanceDanceAutomation:\n\teasy:\n\t3:\n\t0.000,0.000,0.000,0.000,0.000:\n";
	stepFile << info6;
	GeneratePatterns(waveform, barData, cliques, amplitudeInfo, EasyTransitionProbabilities, Easy_AverageNumberOfPatternsPerMeasure, Easy_StandardDeviationDivider);
	AddPatterns(stepFile);
	mCliquePatterns.clear();
	mPatterns.clear();

	//medium
	info6 = "#NOTES:\n\tdance-single:\n\tDanceDanceAutomation:\n\tmedium:\n\t5:\n\t0.000,0.000,0.000,0.000,0.000:\n";
	stepFile << info6;
	GeneratePatterns(waveform, barData, cliques, amplitudeInfo, MediumTransitionProbabilities, Medium_AverageNumberOfPatternsPerMeasure, Medium_StandardDeviationDivider);
	AddPatterns(stepFile);
	mCliquePatterns.clear();
	mPatterns.clear();

	//hard
	info6 = "#NOTES:\n\tdance-single:\n\tDanceDanceAutomation:\n\thard:\n\t7:\n\t0.000,0.000,0.000,0.000,0.000:\n";
	stepFile << info6;
	GeneratePatterns(waveform, barData, cliques, amplitudeInfo, HardTransitionProbabilities, Hard_AverageNumberOfPatternsPerMeasure, Hard_StandardDeviationDivider);
	AddPatterns(stepFile);
	mCliquePatterns.clear();
	mPatterns.clear();

	//challenge
	info6 = "#NOTES:\n\tdance-single:\n\tDanceDanceAutomation:\n\tchallenge:\n\t9:\n\t0.000,0.000,0.000,0.000,0.000:\n";
	stepFile << info6;
	GeneratePatterns(waveform, barData, cliques, amplitudeInfo, ChallengeTransitionProbabilities, Challenge_AverageNumberOfPatternsPerMeasure, Challenge_StandardDeviationDivider);
	AddPatterns(stepFile);
	mCliquePatterns.clear();
	mPatterns.clear();

	stepFile.close();

}


void StepChartGenerator::FindMeasureTypesAndBeatLocations(const BarData& barData, const vector<vector<size_t>>& cliques)
{
	mCliqueMeasureBeatLocations.resize(cliques.size());
	mCliqueMeasureTypes.resize(cliques.size());

	size_t measureCount = 0;

	for (auto& clique : cliques)
	{
		size_t numberOfMatchesThirtySecondBeat = 0;
		size_t numberOfMatchesTwentyFourthBeat = 0;

		vector<float_t> diffs;

		auto& bars = barData.GetBars().at((size_t)clique.at(0) - 1);

		for (size_t i = 0; i < bars.Bars.size(); ++i)
		{
			diffs.push_back(TimeStamp::TimeStampToMilliseconds(bars.Bars.at(i)) - bars.BarStartTimeMilliseconds);
		}

		size_t j, k;

		vector<size_t> ThirtySecondBeatLocations;
		vector<size_t> TwentyFourthBeatLocations;

		for (auto& diff : diffs)
		{
			for (j = 0; j < 32; ++j)
			{
				float_t diff32 = (fabs(diff - (mTimeMillisecondsThirtySecondOfABar * j)));
				if (diff32 < ErrorTolerance)
				{
					++numberOfMatchesThirtySecondBeat;
					break;
				}
			}
			ThirtySecondBeatLocations.push_back(j);

			for (k = 0; k < 24; ++k)
			{
				float_t diff24 = (fabs(diff - (mTimeMillisecondsTwentyFourthOfABar * k)));
				if (diff24 < ErrorTolerance)
				{
					++numberOfMatchesTwentyFourthBeat;
					break;
				}
			}
			TwentyFourthBeatLocations.push_back(k);
		}

		mCliqueMeasureTypes.at(measureCount) = (numberOfMatchesThirtySecondBeat >= numberOfMatchesTwentyFourthBeat);

		if (mCliqueMeasureTypes.at(measureCount))
		{
			for (auto& location : ThirtySecondBeatLocations)
			{
				mCliqueMeasureBeatLocations.at(measureCount).push_back(location);
			}
		}
		else
		{
			for (auto& location : TwentyFourthBeatLocations)
			{
				mCliqueMeasureBeatLocations.at(measureCount).push_back(location);
			}
		}

		++measureCount;
		ThirtySecondBeatLocations.clear();
		TwentyFourthBeatLocations.clear();
	}
}


void StepChartGenerator::GeneratePatterns(const Waveform& waveform, const BarData& barData, const vector<vector<size_t>>& cliques, const AmplitudeInfo& amplitudeInfo,
	const map<const string, map<const string, size_t>>& TransitionProbabilities, const size_t AverageNumberOfPatternsPerMeasure, const float_t StandardDeviationDivider)
{
	mCliquePatterns.resize(cliques.size());

	vector<pair<string, size_t>> numberOfPatternsInEachClique;
	numberOfPatternsInEachClique.resize(cliques.size());

	//find the number of patterns in each clique and the type of pattern they should be based on their average amplitude
	size_t cliqueCount = 0;
	for (auto& numberOfPatterns : numberOfPatternsInEachClique)
	{
		if((amplitudeInfo.GetAverageAmplitudesPerClique().at(cliqueCount) < (amplitudeInfo.GetAverageAmplitude() + amplitudeInfo.GetStandardDeviation()) / StandardDeviationDivider) &&
			(amplitudeInfo.GetAverageAmplitudesPerClique().at(cliqueCount) >= (amplitudeInfo.GetAverageAmplitude() - amplitudeInfo.GetStandardDeviation()) / StandardDeviationDivider))
		{
			numberOfPatterns.first = "Common";
		}
		if ((amplitudeInfo.GetAverageAmplitudesPerClique().at(cliqueCount) >= (amplitudeInfo.GetAverageAmplitude() + amplitudeInfo.GetStandardDeviation()) / StandardDeviationDivider))
		{
			numberOfPatterns.first = "Medium";
		}
		if ((amplitudeInfo.GetAverageAmplitudesPerClique().at(cliqueCount) >= (amplitudeInfo.GetAverageAmplitude() + (amplitudeInfo.GetStandardDeviation() * 1.5)) / StandardDeviationDivider))
		{
			numberOfPatterns.first = "Rare";
		}

		numberOfPatterns.second = static_cast<size_t>((amplitudeInfo.GetAverageAmplitudesPerClique().at(cliqueCount) / amplitudeInfo.GetAverageAmplitude()) * AverageNumberOfPatternsPerMeasure);
		if (numberOfPatterns.second < AverageNumberOfPatternsPerMeasure)
		{
			numberOfPatterns.second = AverageNumberOfPatternsPerMeasure;
		}

		++cliqueCount;
	}

	//let the first pattern be a random common pattern
	auto it = TransitionProbabilities.at("Common").begin();
	advance(it, RandomNumberGenerator(0, TransitionProbabilities.at("Common").size() - 1));
	string firstPatternGenerated = it->first.substr(0, 4);
	string previousPattern = firstPatternGenerated;

	//now, for each clique measure...
	size_t measureCount = 0;
	for (auto& cliqueMeasure : mCliquePatterns)
	{
		//resize to either 32 or 24 based on previous calculations
		cliqueMeasure.resize(mCliqueMeasureTypes.at(measureCount) ? 32 : 24);

		//cache the locations of beats where arrow patterns MUST exist
		vector<size_t> beatLocations(mCliqueMeasureBeatLocations.at(measureCount));
		auto result(std::unique(beatLocations.begin(), beatLocations.end()));
		beatLocations.erase(result, beatLocations.end());

		//if the number of patterns to be generated in the clique is more than the number of beat locations, sprinkle some extra patterns in locations with higher amplitude
		if (beatLocations.size() < numberOfPatternsInEachClique.at(measureCount).second)
		{
			float_t timeIncrement = ((cliqueMeasure.size() == 32) ? mTimeMillisecondsThirtySecondOfABar : mTimeMillisecondsTwentyFourthOfABar);
			vector<pair<int16_t, size_t>> amplitudes;

			size_t extraNumberOfBeatsToBeFound = numberOfPatternsInEachClique.at(measureCount).second - beatLocations.size();
			size_t beatCount = 0;
			for (size_t i = 0; i < cliqueMeasure.size(); ++i)
			{
				size_t sampleNumber = amplitudeInfo.MillisecondsToSampleNumber(waveform.GetSampleRate(), (barData.GetBars().at((size_t)cliques.at(measureCount).at(0) - 1).BarStartTimeMilliseconds + (timeIncrement * i)));
				if (waveform.GetData().at(sampleNumber) >= amplitudeInfo.GetAverageAmplitude() && find(beatLocations.begin(), beatLocations.end(), i) == beatLocations.end())
				{
					amplitudes.push_back(make_pair(waveform.GetData().at(sampleNumber), i));
					++beatCount;
				}
			}
			std::sort(amplitudes.begin(), amplitudes.end());
			std::reverse(amplitudes.begin(), amplitudes.end());
			for (size_t i = 0; i < ((extraNumberOfBeatsToBeFound <= amplitudes.size()) ? extraNumberOfBeatsToBeFound : amplitudes.size()); ++i)
			{
				beatLocations.push_back(amplitudes.at(i).second);
			}
			std::sort(beatLocations.begin(), beatLocations.end());
		}

		size_t beatTracker = 0;
		//iterate through the clique measure
		for (size_t i = 0; i < cliqueMeasure.size(); ++i)
		{
			//initialize the pattern to 0000
			cliqueMeasure.at(i) = "0000";

			//if the current measure index is a beat location...
			if ((beatTracker < beatLocations.size()) && (i == beatLocations.at(beatTracker)))
			{
				//find all possible transitions from the previous pattern that was generated
				vector<pair<string, size_t>> possibleTransitions;

				for (auto& transition : TransitionProbabilities.at(numberOfPatternsInEachClique.at(measureCount).first))
				{
					if (transition.first.substr(0, 4) == previousPattern)
					{
						possibleTransitions.push_back(transition);
					}
				}

				//if such a transition was not found in the specified group, find it in the other groups
				if (possibleTransitions.size() == 0)
				{
					for (auto& transitionTypes : TransitionProbabilities)
					{
						if (transitionTypes.first != numberOfPatternsInEachClique.at(measureCount).first)
						{
							for (auto& transition : transitionTypes.second)
							{
								if (transition.first.substr(0, 4) == previousPattern)
								{
									possibleTransitions.push_back(transition);
								}
							}
						}
					}
				}

				//technically, you should never end up here.
				if (possibleTransitions.size() == 0)
				{
					cout << endl << "Invalid transition data.";
					throw exception("Invalid transition data.");
				}

				//select a transition from the possible transitions using weighted randomness
				size_t sumOfWeights = 0;
				for (auto& possibleTransition : possibleTransitions)
				{
					sumOfWeights += possibleTransition.second;
				}

				//float_t randomNumber = static_cast<float_t>((rand() / (static_cast<float_t>(RAND_MAX / sumOfWeights))));
				string selectedPattern;
				//float_t checkSum = 0.0f;
				size_t randomNumber = RandomNumberGenerator(0, sumOfWeights);
				size_t checkSum = 0;
				for (auto& possibleTransition : possibleTransitions)
				{
					checkSum += possibleTransition.second;
					if (randomNumber <= checkSum)
					{
						selectedPattern = possibleTransition.first.substr(6, string::npos);
						break;
					}
				}

				//add the selected pattern to the clique measure
				cliqueMeasure.at(i) = selectedPattern;
				previousPattern = cliqueMeasure.at(i);

				++beatTracker;
			}

		}

		++measureCount;
	}

	mPatterns.resize(barData.GetBars().size());

	cliqueCount = 0;
	for (auto& clique : cliques)
	{
		for (auto& barNumber : clique)
		{
			mPatterns.at((size_t)barNumber - 1) = mCliquePatterns.at(cliqueCount);
		}

		++cliqueCount;
	}
}


size_t StepChartGenerator::RandomNumberGenerator(size_t min, size_t max)
{
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<size_t> dist(min, max);

	return dist(eng);
}


void StepChartGenerator::AddPatterns(fstream& stepFile)
{
	size_t measureCount = 0;
	for (auto& measure : mPatterns)
	{
		for (auto& pattern : measure)
		{
			stepFile << pattern << endl;
		}
		++measureCount;
		if(measureCount < mPatterns.size())
			stepFile << "," << endl;
	}
	stepFile << ";" << endl;
}