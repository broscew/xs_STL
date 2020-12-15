#ifndef __XS_ALGORITHMS__
#define __XS_ALGORITHMS__

namespace xs
{
	namespace algo
	{

	}

	namespace c_algo
	{
		namespace detail
		{
			template<typename output_itr, typename value_type, size_t ... N>
			inline constexpr output_itr fill_n_impl(output_itr begin, value_type value, std::index_sequence<N...>)
			{
				((*(begin + N) = value), ...);

				return begin;
			}


			constexpr size_t integral_pow_impl(size_t base, size_t exp, size_t result = 1)
			{
				return exp < 1 ? result : integral_pow_impl(base * base, exp / 2, (exp % 2) ? result * base : result);
			}
		}


		template <typename lhs_itr, typename rhs_itr>
		inline constexpr bool is_equal(lhs_itr in_lbegin, lhs_itr in_lend, rhs_itr in_rbegin, rhs_itr in_rend)
		{
			return ((in_lbegin != in_lend) && (in_rbegin != in_rend)) ?
				(*in_lbegin == *in_rbegin) && is_equal(in_lbegin + 1, in_lend, in_rbegin + 1, in_rend) :
				((in_lbegin == in_lend) && (in_rbegin == in_rend));
		}

		template <size_t N, typename output_itr, typename value_type>
		inline constexpr output_itr fill_n(output_itr begin, value_type value)
		{
			return detail::fill_n_impl(begin, value, std::make_index_sequence<N>{});
		}

		inline constexpr size_t log_2_int (size_t x, int p = 0) noexcept
		{
			return (x <= 1) ? p : log_2_int(x >> 1, p + 1);
		}

		constexpr size_t integral_pow(size_t base, size_t exp)
		{
			return detail::integral_pow_impl(base, exp);
		}

		template<typename Lambda, typename ... Ts>
		void for_each_arguments(Lambda&& func, Ts&& ... args)
		{
			((void)func(std::forward<Ts>(args)), ...);
		}

		template <typename Container_Type, typename Lambda>
		void for_each_element(Container_Type&& container, Lambda&& func)
		{
			for (auto& elem : container)
			{
				func(elem);
			}
		}
	}
}

#endif