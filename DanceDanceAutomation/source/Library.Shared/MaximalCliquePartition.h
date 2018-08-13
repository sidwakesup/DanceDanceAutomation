#pragma once

namespace DanceDanceAutomation
{

	class MaximalCliquePartition
	{
	public:
		MaximalCliquePartition(const std::vector<std::uint64_t>& adjacencyMatrix);
		MaximalCliquePartition(const MaximalCliquePartition& other) = default;
		MaximalCliquePartition(MaximalCliquePartition&& other) = default;
		MaximalCliquePartition& operator=(const MaximalCliquePartition& other) = default;
		MaximalCliquePartition& operator=(MaximalCliquePartition&& other) = default;
		~MaximalCliquePartition() = default;

		const std::vector<std::vector<std::size_t>>& Cliques() const;

		void BronKerbosch(std::uint64_t R, std::uint64_t P, std::uint64_t X, std::vector<uint64_t>& cliques);

	private:
		std::vector<std::uint64_t> mAdjacencyMatrix;
		std::size_t mAdjacencyMatrixSize;
		std::vector<std::vector<std::size_t>> mCliques;

	};

}