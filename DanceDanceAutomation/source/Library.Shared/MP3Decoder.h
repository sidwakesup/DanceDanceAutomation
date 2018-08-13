#pragma once

namespace DanceDanceAutomation
{

	class MP3Decoder final
	{

	public:

		MP3Decoder(const char *inputFileName);
		MP3Decoder(const MP3Decoder& other) = delete;
		MP3Decoder(MP3Decoder&& other) = default;
		MP3Decoder& operator=(const MP3Decoder& other) = delete;
		MP3Decoder& operator=(MP3Decoder&& other) = default;
		~MP3Decoder() = default;

		inline const std::string& OutputFileName() const { return mOutputFileName; }

	private:

		static unsigned short read16le(const void *p);
		static char *wav_header(int hz, int ch, int bips, int data_bytes);
		static unsigned char *preload(FILE *file, int *data_size);
		static void decode_file(const unsigned char *buf_mp3, int mp3_size, const unsigned char *buf_ref, int ref_size, FILE *file_out, const int wave_out);

		std::string mOutputFileName;
	};

}