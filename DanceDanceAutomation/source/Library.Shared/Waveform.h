#pragma once

namespace DanceDanceAutomation
{

	class Waveform final
	{

	public:

		explicit Waveform(const std::string& fileName);
		Waveform(const Waveform& other) = default;
		Waveform(Waveform&& other) = default;
		Waveform& operator=(const Waveform& other) = default;
		Waveform& operator=(Waveform&& other) = default;
		~Waveform() = default;

		std::uint16_t GetNumChannels() const;
		std::uint16_t GetBitsPerSample() const;
		std::uint32_t GetSampleRate() const;
		std::uint32_t GetNumSamplesPerChannel() const;
		const std::vector<std::uint16_t>& GetData() const;

	private:

		std::uint16_t mNumChannels;
		std::uint16_t mBitsPerSample;
		std::uint32_t mSampleRate;
		std::uint32_t mNumSamplesPerChannel;
		std::vector<std::uint16_t> mData;

	};

}