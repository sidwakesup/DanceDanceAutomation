#include "pch.h"
#include "MaximalCliquePartition.h"

using namespace std;
using namespace DanceDanceAutomation;

MaximalCliquePartition::MaximalCliquePartition(const vector<uint64_t>& adjacencyMatrix) :
	mAdjacencyMatrix(adjacencyMatrix), mAdjacencyMatrixSize(adjacencyMatrix.size())
{
	uint64_t lbit = 1;
	uint64_t mask = 0;
	for (size_t i = 0; i < mAdjacencyMatrixSize; ++i)
	{
		mask = mask | (lbit << i);
	}

	uint64_t R = 0;
	uint64_t P = mask;
	uint64_t X = 0;

	vector<uint64_t> cliques;
	BronKerbosch(R, P, X, cliques);

	mCliques.resize(cliques.size());
	for (size_t i = 0; i < cliques.size(); ++i)
	{
		lbit = 1;
		for (size_t j = 0; j < mAdjacencyMatrixSize; ++j)
		{
			if (((cliques[i] & (lbit << (mAdjacencyMatrixSize - (j + 1)))) > 0))
			{
				mCliques[i].push_back(j + 1);
			}
		}
	}

}


const vector<vector<size_t>>& MaximalCliquePartition::Cliques() const
{
	return mCliques;
}


void MaximalCliquePartition::BronKerbosch(uint64_t R, uint64_t P, uint64_t X, vector<uint64_t>& cliques)
{
	uint64_t v, single;
	if ((P == 0) && (X == 0))
	{
		cliques.push_back(R);
	}
	else
	{
		single = 1;
		for (size_t i = 0; i < mAdjacencyMatrixSize; ++i)
		{
			v = single << (mAdjacencyMatrixSize - 1 - i);
			if (P & v)
			{
				P = P ^ v;
				BronKerbosch((R | v), (P & mAdjacencyMatrix.at(i)), (X & mAdjacencyMatrix.at(i)), cliques);
				X = X | v;
			}
		}
	}
}