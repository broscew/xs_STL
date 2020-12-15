#ifndef  __XS_HASH__
#define __XS_HASH__

namespace xs
{
	namespace hash
	{
		namespace details
		{
			static constexpr size_t offset_basis = 14695981039346656037ull;
			static constexpr size_t offset_prime = 1099511628211ull;
		}

		constexpr size_t fnv1a(size_t n, const char* str, size_t hash = details::offset_basis)
		{
			return n > 0 ? fnv1a(n - 1, str + 1, (hash ^ *str) * details::offset_prime) : hash;
		}

		template <size_t N>
		constexpr size_t fnv1a(const char(&array)[N])
		{
			return fnv1a(N - 1, &array[0]);
		}
	}
}

#endif // ! __XS_HASH__
