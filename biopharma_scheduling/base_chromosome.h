#if defined(__posix) || defined(__unix) || defined(__linux) || defined(__APPLE__)
 	// #pragma GCC diagnostic ignored "-Wreorder"
	// #pragma GCC diagnostic ignored "-Wunused-variable"
	#pragma GCC diagnostic ignored "-Wformat="
	#pragma GCC diagnostic ignored "-Wsign-compare"
#endif 

#ifndef __BASE_CHROMOSOME__
#define __BASE_CHROMOSOME__

#include <vector>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <functional>
#include <cassert>

#include "utils.h"


namespace types
{
	/*
		Base dynamic individual class. Not to be called directly.
	*/
	template<class Gene>
	class BaseChromosome
	{
	public:
		typedef std::vector<Gene> Genes;

		explicit BaseChromosome() {}

		template<class... GeneParams>
		explicit BaseChromosome(
			int starting_length,
			double p_xo,
			double p_gene_swap,
			GeneParams... params
		) :
			p_xo(p_xo),
			p_gene_swap(p_gene_swap)

		{
			while (starting_length-- > 0) {
				genes.push_back(std::move(Gene(params...)));
			}

			assert(starting_length == -1);
			assert(genes.size() >= 1);
		}

		inline void Cross(BaseChromosome &other) 
		{
			if (utils::random() > p_xo) {
				return;
			}

			if (genes.size() < 2 || other.genes.size() < 2) {
				return;
			}

			int i;

			if (genes.size() < other.genes.size()) {
				for (i = 0; i != genes.size(); ++i) {
					if (utils::random() <= 0.50) {
						std::swap(genes[i], other.genes[i]);
					}
				}
				for (; i != other.genes.size(); ++i) {
					if (utils::random() <= 0.50) {
						genes.push_back(other.genes[i]);
					}
				}
			}
			else {
				for (i = 0; i != other.genes.size(); ++i) {
					if (utils::random() <= 0.50) {
						std::swap(genes[i], other.genes[i]);
					}
				}
				for (; i != genes.size(); ++i) {
					if (utils::random() <= 0.50) {
						other.genes.push_back(genes[i]);
					}
				}
			}
		}

		inline void Mutate() 
		{
			for (auto &gene : genes) {
				gene.Mutate();
			}
			
			AddGene();
			SwapGenes();
		}

		Genes genes;

	private:
		inline void AddGene()
		{
			genes.push_back(genes.back().make_new());
		}

		inline void SwapGenes()
		{
			if (utils::random() >= p_gene_swap) {
				return;
			}

			int g1 = 0, g2 = 0;

			do {
				g1 = utils::random_int(0, genes.size() - 1);
				g2 = utils::random_int(0, genes.size() - 1);
			} while (g1 == g2);

			std::swap(genes[g1], genes[g2]);
		}

		double p_xo;
		double p_gene_swap;
	};
}

#endif 