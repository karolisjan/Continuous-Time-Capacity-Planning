#ifndef  __GENE_H__
#define __GENE_H__

#include "utils.h"

namespace types
{
	struct Gene
	{
		Gene() {}

		Gene(
			int num_products,
			int num_usp_suites,
			double p_product_mut = 0.141214,
			double p_usp_suite_mut = 0.141214,
			double p_plus_batch_mut = 0.121224,
			double p_minus_batch_mut = 0.213939
		) :
			num_products(num_products),
			num_usp_suites(num_usp_suites),
			p_product_mut(p_product_mut),
			p_usp_suite_mut(p_usp_suite_mut),
			p_plus_batch_mut(p_plus_batch_mut),
			p_minus_batch_mut(p_minus_batch_mut),
			num_batches(1)
		{
			product_num = utils::random_int(1, num_products + 1);
			usp_suite_num = utils::random_int(1, num_usp_suites + 1);
		}

		Gene make_new()
		{
			return Gene(
				num_products, 
				num_usp_suites, 
				p_product_mut, 
				p_usp_suite_mut, 
				p_plus_batch_mut, 
				p_minus_batch_mut
			);
		}

		inline void mutate()
		{
			mutate_product_num();
			mutate_usp_suite_num();
			mutate_num_batches();
		}

		int product_num, num_batches, usp_suite_num;

	private:
		inline void mutate_product_num()
		{
			if (utils::random() >= p_product_mut)
				return;

			int random_product_num;
			do { random_product_num = utils::random_int(1, num_products + 1); }
			while (product_num == random_product_num);
			product_num = random_product_num;
		}

		inline void mutate_usp_suite_num()
		{
			if (utils::random() >= p_usp_suite_mut)
				return;

			int random_usp_suite_num;
			do { random_usp_suite_num = utils::random_int(1, num_usp_suites + 1); } while (usp_suite_num == random_usp_suite_num);
			usp_suite_num = random_usp_suite_num;
		}

		inline void mutate_num_batches()
		{
			if (utils::random() < p_plus_batch_mut)
				num_batches += 1;

			if (utils::random() < p_minus_batch_mut) {
				if (num_batches > 1)
					num_batches -= 1;
			}
		}

		int num_products, num_usp_suites;
		double p_product_mut, p_usp_suite_mut, p_plus_batch_mut, p_minus_batch_mut;
	};
}

#endif // ! __GENE_H__

