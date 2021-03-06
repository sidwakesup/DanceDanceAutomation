#include "pch.h"

using namespace std;

struct PatternData
{
	size_t numberOfPatterns;
	size_t numberOfMeasures;
	size_t averageNumberOfPatternsPerMeasure;
	map<string, size_t> transitionCount;

	PatternData() : numberOfPatterns(0), numberOfMeasures(0), averageNumberOfPatternsPerMeasure(0), transitionCount() {}
};

enum class Difficulty
{
	CHALLENGE,
	HARD,
	MEDIUM,
	EASY,
	BEGINNER,
	MAX
};

static const vector<string> DifficultyEnumToString{ "Challenge", "Hard", "Medium", "Easy", "Beginner" };

int main(int argc, char* argv[])
{
	static const size_t DISTANCE = 4;

	if (argc < 2)
	{
		return EXIT_FAILURE;
	}

	vector<PatternData> patternData;
	patternData.resize(static_cast<size_t>(Difficulty::MAX));
	size_t numberOfStepChartsRead = 0;

	for (auto& file : filesystem::recursive_directory_iterator(argv[1]))
	{
		if (filesystem::is_regular_file(file.path()) && file.path().extension() == ".sm")
		{
			ifstream simFile;
			simFile.open(file.path().string(), ios_base::in);
			if (simFile.bad())
			{
				throw std::exception("Invalid file read.");
			}

			while (!simFile.eof())
			{
				string buffer("");
				while (!simFile.eof() && buffer != "#NOTES:")
				{
					getline(simFile, buffer);
				}

				getline(simFile, buffer);

				if (buffer.find("dance-single") != string::npos)
				{
					getline(simFile, buffer);
					getline(simFile, buffer);

					PatternData* patternDataForSpecificDifficulty = nullptr;

					if (buffer.find("Challenge") != string::npos)
					{
						patternDataForSpecificDifficulty = &patternData[static_cast<size_t>(Difficulty::CHALLENGE)];
					}
					else if (buffer.find("Hard") != string::npos)
					{
						patternDataForSpecificDifficulty = &patternData[static_cast<size_t>(Difficulty::HARD)];
					}
					else if (buffer.find("Medium") != string::npos)
					{
						patternDataForSpecificDifficulty = &patternData[static_cast<size_t>(Difficulty::MEDIUM)];
					}
					else if (buffer.find("Easy") != string::npos)
					{
						patternDataForSpecificDifficulty = &patternData[static_cast<size_t>(Difficulty::EASY)];
					}
					else if (buffer.find("Beginner") != string::npos)
					{
						patternDataForSpecificDifficulty = &patternData[static_cast<size_t>(Difficulty::BEGINNER)];
					}

					if (patternDataForSpecificDifficulty == nullptr)
					{
						continue;
					}

					while (!simFile.eof() && buffer.size() != 4)
					{
						getline(simFile, buffer);
					}

					vector<string> patterns;

					while (!simFile.eof() && buffer != ";")
					{
						if (buffer.find(",") != string::npos)
						{
							++patternDataForSpecificDifficulty->numberOfMeasures;
						}

						if (buffer.find("//") == string::npos &&
							buffer.find(",") == string::npos &&
							buffer.find("4") == string::npos &&
							buffer.find("M") == string::npos &&
							buffer.find("L") == string::npos &&
							buffer.find("F") == string::npos)
						{
							for (size_t i = 0; i < 4; ++i)
							{
								if (buffer[i] == '2' || buffer[i] == '3')
								{
									buffer[i] = '1';
								}
							}

							patterns.push_back(buffer);
						}

						getline(simFile, buffer);
					}

					patternDataForSpecificDifficulty->numberOfPatterns += patterns.size();

					for (size_t i = 0; i < patterns.size() - DISTANCE; ++i)
					{
						if (patterns[i] != "0000")
						{
							size_t j = 1;
							while (j <= DISTANCE)
							{
								if (patterns[i + j] != "0000")
								{
									string key = patterns[i] + "->" + patterns[i + j];
									patternDataForSpecificDifficulty->transitionCount[key] += 1;
									break;
								}
								++j;
							}
						}
					}

					patternDataForSpecificDifficulty->averageNumberOfPatternsPerMeasure =
						patternDataForSpecificDifficulty->numberOfPatterns / patternDataForSpecificDifficulty->numberOfMeasures;

					patterns.clear();
					++numberOfStepChartsRead;

				}
			}

			simFile.close();
		}
	}

	ofstream trendDataFile;
	trendDataFile.open("DDRTrendsData.txt", ios_base::out);

	trendDataFile << "\nDDR Trend Data\n";

	for (size_t i = 0; i < static_cast<size_t>(Difficulty::MAX); ++i)
	{
		trendDataFile << endl << DifficultyEnumToString[i] << ":" << endl;
		trendDataFile << "Number of Patterns: " << patternData[i].numberOfPatterns << endl;
		trendDataFile << "Number of Measures: " << patternData[i].numberOfMeasures << endl;
		trendDataFile << "Average Number of Patterns per Measure: " << patternData[i].averageNumberOfPatternsPerMeasure << endl;
		trendDataFile << "Transitions: " << endl;
		for (auto& transition : patternData[i].transitionCount)
		{
			trendDataFile << transition.first << " " << transition.second << endl;
		}
	}

	trendDataFile.close();

    return EXIT_SUCCESS;
}

