#include "pch.h"

#define MINIMP3_ONLY_MP3
#define MINIMP3_IMPLEMENTATION

#include "minimp3/minimp3.h"
#include "MP3Decoder.h"


using namespace DanceDanceAutomation;
using namespace std;


MP3Decoder::MP3Decoder(const char *input_file_name)
{
	int wave_out = 0, ref_size, mp3_size;
	FILE *file_out = nullptr;

	std::string ref_file_name(input_file_name);
	size_t pos = ref_file_name.find(".mp3");
	if (pos != std::string::npos)
	{
		ref_file_name = ref_file_name.erase(pos, std::string(".mp3").length());
	}
	else
	{
		throw std::exception("Invalid file extension.");
	}
	mOutputFileName = ref_file_name.append(std::string(".wav"));


	fopen_s(&file_out, mOutputFileName.c_str(), "wb");
	const char *ext = strrchr(mOutputFileName.c_str(), '.');

	if (ext && !(_strnicmp(ext + 1, "wav", strlen("wav"))))
	{
		wave_out = 1;
	}

	FILE *file_ref = nullptr;
	fopen_s(&file_ref, ref_file_name.c_str(), "rb");
	unsigned char *buf_ref = preload(file_ref, &ref_size);
	if (file_ref)
		fclose(file_ref);

	if (!input_file_name)
	{
		throw std::exception("error: no file names given\n");
	}

	FILE *file_mp3 = nullptr;
	fopen_s(&file_mp3, input_file_name, "rb");
	unsigned char *buf_mp3 = preload(file_mp3, &mp3_size);
	if (file_mp3)
		fclose(file_mp3);
	if (!buf_mp3 || !mp3_size)
	{
		throw std::exception("error: no input data\n");
	}
	decode_file(buf_mp3, mp3_size, buf_ref, ref_size, file_out, wave_out);

	if (buf_mp3)
		free(buf_mp3);
	if (buf_ref)
		free(buf_ref);
	if (file_out)
		fclose(file_out);
}


unsigned short MP3Decoder::read16le(const void *p)
{
	const unsigned char *src = static_cast<const unsigned char *>(p);
	return ((src[0]) << 0) | ((src[1]) << 8);
}


char* MP3Decoder::wav_header(int hz, int ch, int bips, int data_bytes)
{
	static char hdr[45] = "RIFFsizeWAVEfmt \x10\0\0\0\1\0ch_hz_abpsbabsdatasize";
	unsigned long nAvgBytesPerSec = bips * ch*hz >> 3;
	unsigned int nBlockAlign = bips * ch >> 3;

	*(static_cast<int *>(static_cast<void*>(hdr + 0x04))) = 44 + data_bytes - 8;   /* File size - 8 */
	*(static_cast<short *>(static_cast<void*>(hdr + 0x14))) = 1;                     /* Integer PCM format */
	*(static_cast<short *>(static_cast<void*>(hdr + 0x16))) = static_cast<short>(ch);
	*(static_cast<int *>(static_cast<void*>(hdr + 0x18))) = hz;
	*(static_cast<int *>(static_cast<void*>(hdr + 0x1C))) = nAvgBytesPerSec;
	*(static_cast<short *>(static_cast<void*>(hdr + 0x20))) = static_cast<short>(nBlockAlign);
	*(static_cast<short *>(static_cast<void*>(hdr + 0x22))) = static_cast<short>(bips);
	*(static_cast<int *>(static_cast<void*>(hdr + 0x28))) = data_bytes;
	return hdr;
}


unsigned char* MP3Decoder::preload(FILE *file, int *data_size)
{
	unsigned char *data;
	*data_size = 0;
	if (!file)
		return 0;
	if (fseek(file, 0, SEEK_END))
		return 0;
	*data_size = (int)ftell(file);
	if (*data_size < 0)
		return 0;
	if (fseek(file, 0, SEEK_SET))
		return 0;
	data = (unsigned char*)malloc(*data_size);
	if (!data)
		return 0;
	if ((int)fread(data, 1, *data_size, file) != *data_size)
		exit(1);
	return data;
}


void MP3Decoder::decode_file(const unsigned char *buf_mp3, int mp3_size, const unsigned char *buf_ref, int ref_size, FILE *file_out, const int wave_out)
{
	static mp3dec_t mp3d;
	mp3dec_frame_info_t info;
	int i, data_bytes, samples, total_samples = 0, maxdiff = 0;
	double MSE = 0.0, psnr;

	mp3dec_init(&mp3d);
	memset(&info, 0, sizeof(info));

	if (wave_out && file_out)
		fwrite(wav_header(0, 0, 0, 0), 1, 44, file_out);
	do
	{
		short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];

		samples = mp3dec_decode_frame(&mp3d, buf_mp3, mp3_size, pcm, &info);

		if (samples)
		{
			total_samples += samples * info.channels;
			if (buf_ref && ref_size >= samples * info.channels * 2)
			{
				for (i = 0; i < samples*info.channels; i++)
				{
					int MSEtemp = abs(static_cast<int>(pcm[i]) - static_cast<int>(static_cast<short>(read16le(&buf_ref[i * sizeof(short)]))));
					if (MSEtemp > maxdiff)
						maxdiff = MSEtemp;
					MSE += static_cast<float>(MSEtemp) * static_cast<float>(MSEtemp);
				}
				buf_ref += samples * info.channels * 2;
				ref_size -= samples * info.channels * 2;
			}
			if (file_out)
				fwrite(pcm, samples, 2 * info.channels, file_out);
		}
		buf_mp3 += info.frame_bytes;
		mp3_size -= info.frame_bytes;
	} while (info.frame_bytes);

	MSE /= total_samples ? total_samples : 1;
	if (0 == MSE)
		psnr = 99.0;
	else
		psnr = 10.0*log10((static_cast<double>(0x7fff * 0x7fff)) / MSE);
	//printf("rate=%d samples=%d max_diff=%d PSNR=%f\n", info.hz, total_samples, maxdiff, psnr);
	if (psnr < 96)
	{
		throw std::exception("PSNR compliance failed\n");
	}

	if (wave_out && file_out)
	{
		data_bytes = ftell(file_out) - 44;
		rewind(file_out);
		fwrite(wav_header(info.hz, info.channels, 16, data_bytes), 1, 44, file_out);
	}
}