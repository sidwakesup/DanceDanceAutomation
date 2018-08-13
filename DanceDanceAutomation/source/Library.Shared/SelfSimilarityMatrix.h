#pragma once

namespace DanceDanceAutomation
{

	template<typename T, typename DifferenceFunction>
	class SelfSimilarityMatrix final
	{
	public:
		explicit SelfSimilarityMatrix(const std::vector<T>& sampleData, std::float_t errorTolerance);
		SelfSimilarityMatrix(const SelfSimilarityMatrix& other) = default;
		SelfSimilarityMatrix(SelfSimilarityMatrix&& other) = default;
		SelfSimilarityMatrix& operator=(const SelfSimilarityMatrix& other) = default;
		SelfSimilarityMatrix& operator=(SelfSimilarityMatrix&& other) = default;
		~SelfSimilarityMatrix() = default;

		const std::vector<std::vector<std::float_t>> GetSimilarities() const;
		const std::vector<std::uint64_t> GetAdjacencyMatrix() const;

	private:
		std::vector<T> mSampleData;
		std::vector<std::vector<std::float_t>> mSimilarities;
		std::vector<std::uint64_t> mAdjacencyMatrix;
	};

	template<typename T, typename DifferenceFunction>
	SelfSimilarityMatrix<T, DifferenceFunction>::SelfSimilarityMatrix(const std::vector<T>& sampleData, std::float_t errorTolerance) :
		mSampleData(sampleData)
	{
		std::size_t sampleDataSize = mSampleData.size();
		DifferenceFunction difference;

		mAdjacencyMatrix.resize(sampleDataSize);
		mSimilarities.resize(sampleDataSize);
		for (size_t i = 0; i < mSimilarities.size(); ++i)
		{
			mSimilarities[i].resize(sampleDataSize);
		}

		uint64_t lbit = 1;
		uint8_t bit = 0;
		for (std::size_t i = 0; i < sampleDataSize; ++i)
		{
			std::uint64_t sum = 0;
			for (std::size_t j = 0; j < sampleDataSize; ++j)
			{
				if (j < i)
				{
					lbit = 1;
					bit = 0;
					if ((mAdjacencyMatrix[j] & (lbit << (sampleDataSize - i - 1))) > 0)
					{
						bit = 1;
					}
					mSimilarities[i][j] = mSimilarities[j][i];
				}
				if (i == j)
				{
					mSimilarities[i][j] = std::numeric_limits<std::float_t>::max();
					bit = 0;
				}
				if(j > i)
				{
					mSimilarities[i][j] = static_cast<std::float_t>(fabs(difference(mSampleData[i], mSampleData[j])));
					bit = ((mSimilarities[i][j] <= errorTolerance) ? 1 : 0);
				}
				sum = (sum << 1) | bit;
			}
			mAdjacencyMatrix[i] = sum;
		}
	}


	template<typename T,  typename DifferenceFunction>
	const std::vector<std::vector<std::float_t>> SelfSimilarityMatrix<T, DifferenceFunction>::GetSimilarities() const
	{
		return mSimilarities;
	}


	template<typename T, typename DifferenceFunction>
	const std::vector<std::uint64_t> SelfSimilarityMatrix<T, DifferenceFunction>::GetAdjacencyMatrix() const
	{
		return mAdjacencyMatrix;
	}

}