//#include "pch.h"
//#include "SelfSimilarityMatrix.h"
//
//using namespace std;
//using namespace DanceDanceAutomation;
//
//template<typename T>
//SelfSimilarityMatrix<T>::SelfSimilarityMatrix(const std::vector<T>& sampleData, std::float_t errorTolerance) :
//	mSampleData(sampleData), mErrorTolerance(errorTolerance)
//{
//	size_t sampleDataSize = mSampleData.size();
//
//	mSimilarities.resize(sampleDataSize);
//
//	for (size_t i = 0; i < sampleDataSize; ++i)
//	{
//		for (size_t j = 0; j < sampleDataSize; ++j)
//		{
//			float_t similarity = static_cast<float_t>(fabs(mSampleData[i] - mSampleData[j]));
//			if (similarity <= mErrorTolerance && ((mSimilarities[j] > 0.0f) ? (similarity < mSimilarities[j]) : true))
//			{
//				mSimilarities[i] = similarity;
//				mSimilarities[j] = similarity;
//			}
//		}
//	}
//}
//
//
//template<typename T>
//const vector<float_t> SelfSimilarityMatrix<T>::GetSimilarities() const
//{
//	return mSimilarities;
//}