#include "pch.h"
#include "MP3Decoder.h"
#include "Waveform.h"
#include "BeatDetector.h"
#include "TimeStamp.h"
#include "MiniBpm.h"
#include "SelfSimilarityMatrix.h"
#include "BarData.h"
#include "MaximalCliquePartition.h"
#include "AmplitudeInfo.h"
#include "StepChartGenerator.h"

using namespace std;
using namespace DanceDanceAutomation;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return EXIT_FAILURE;
	}

	cout << "Generating step file.";

	//Decode the mp3 file to obtain the wav file
	MP3Decoder mp3Decoder(argv[1]);

	cout << ".";

	//Store data from the wav file
	Waveform waveform(mp3Decoder.OutputFileName());

	cout << ".";

	//Run the beat detection algorithm
	BeatDetector::Instance()->loadSystem();
	BeatDetector::Instance()->LoadSong(1024, argv[1]);
	BeatDetector::Instance()->setStarted(true);
	vector<TimeStamp> beatTimings;
	while (BeatDetector::Instance()->isPlaying())
	{
		BeatDetector::Instance()->update(beatTimings);
	}

	cout << ".";

	//Calculate the BPM
	vector<float> samples(waveform.GetData().begin(), waveform.GetData().end());
	int32_t numberOfSamples = static_cast<int32_t>(samples.size());
	MiniBPM bpmCalc((float)waveform.GetSampleRate());
	float_t bpm = static_cast<float_t>(round(bpmCalc.estimateTempoOfSamples(&samples[0], numberOfSamples)));

	cout << ".";

	//Generate bar data
	BarData bars(beatTimings, bpm, *BeatDetector::Instance()->getSongLength());

	cout << ".";

	//Form the self-similarity matrix and the adjacency matrix
	SelfSimilarityMatrix<Bar, BarDifferenceFunction> ssm(bars.GetBars(), 50.0f);
	auto similarities(ssm.GetSimilarities());
	auto adjacencyMatrix(ssm.GetAdjacencyMatrix());

	cout << ".";

	//Find the maximal cliques in the undirected graph represented by the adjacency matrix
	MaximalCliquePartition mcp(adjacencyMatrix);
	const auto& cliques = mcp.Cliques();

	cout << ".";

	//Generate amplitude data
	AmplitudeInfo ampInfo(waveform, bars, cliques);

	cout << ".";

	//Generate step file
	StepChartGenerator generator(waveform, bpm, bars, cliques, ampInfo, argv[1]);

	cout << ".";

    return EXIT_SUCCESS;
}

