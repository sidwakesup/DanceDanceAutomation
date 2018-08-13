#include "pch.h"
#include "Waveform.h"

using namespace std;
using namespace DanceDanceAutomation;

Waveform::Waveform(const string& fileName)
{
	fstream wavFile;
	wavFile.open(fileName, ios_base::in | ios_base::binary);

	if (wavFile.bad())
	{
		throw std::exception("Unable to open file!");
	}

	wavFile.unsetf(ios::skipws);

	wavFile.seekg(22);
	wavFile.read(reinterpret_cast<char *>(&mNumChannels), sizeof(mNumChannels));
	wavFile.seekg(24);
	wavFile.read(reinterpret_cast<char *>(&mSampleRate), sizeof(mSampleRate));
	wavFile.seekg(34);
	wavFile.read(reinterpret_cast<char *>(&mBitsPerSample), sizeof(mBitsPerSample));
	wavFile.seekg(40);
	uint32_t dataSize;
	wavFile.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
	mNumSamplesPerChannel = dataSize / ((mNumChannels * mBitsPerSample) / 8);
	wavFile.seekg(44);

	if (mNumChannels == 1)
	{
		uint16_t d;
		for (uint32_t i = 0; i < mNumSamplesPerChannel; ++i)
		{
			wavFile.read(reinterpret_cast<char*>(&d), 2);
			mData.push_back(d);
		}
	}
	else if (mNumChannels == 2)
	{
		uint16_t l, r;
		for (uint32_t i = 0; i < mNumSamplesPerChannel; ++i)
		{
			wavFile.read(reinterpret_cast<char *>(&l), 2);
			wavFile.read(reinterpret_cast<char *>(&r), 2);
			mData.push_back((l + r) / 2);
		}
	}

	wavFile.close();

}


std::uint16_t Waveform::GetNumChannels() const
{
	return mNumChannels;
}


std::uint16_t Waveform::GetBitsPerSample() const
{
	return mBitsPerSample;
}


std::uint32_t Waveform::GetSampleRate() const
{
	return mSampleRate;
}


std::uint32_t Waveform::GetNumSamplesPerChannel() const
{
	return mNumSamplesPerChannel;
}


const std::vector<std::uint16_t>& Waveform::GetData() const
{
	return mData;
}
