#ifndef __XS_HASHMAP__
#define __XS_HASHMAP__
#include <functional>
#include <memory>

namespace xs
{
	namespace ds
	{
		namespace details
		{
			using ctrl_t = int8_t;
			enum CTRL : ctrl_t
			{
				Empty = -128, // 1000 0000
				Deleted = -2, // 1111 1110
				Sentinel = -1 // 1111 1111
			};

			size_t H1(size_t hash)
			{
				return hash >> 7;
			}

			ctrl_t H2(size_t hash)
			{
				return hash & 0x7F;
			}
		}

		template <typename T_KEY, typename T_VALUE>
		struct hash_node
		{
			using key_type = T_KEY;
			using value_type = T_VALUE;

			hash_node() = default;
			hash_node(const hash_node&) = default;
			hash_node(hash_node&&) = default;
			hash_node& operator= (const hash_node&) = default;
			hash_node& operator= (hash_node&&) = default;

			hash_node(key_type type, value_type value)
				:m_key{ std::move(type) }, m_value{ std::move(value)}
			{}

			key_type m_key;
			value_type m_value;
		};

		template<typename T_KEY, typename T_VALUE, size_t Size, typename hashfunc = std::hash<T_KEY>>
		class hashmap_fixed
		{
			using key_type = T_KEY;
			using value_type = T_VALUE;
			using entry = hash_node<T_KEY, T_VALUE>;
			using entry_pointer = hash_node<T_KEY, T_VALUE>;
			using entry_reference = hash_node<T_KEY, T_VALUE>;

			using iterator = iterator<entry>;
			using const_iterator = const_iterator<entry>;
			using reverse_iterator = reverse_iterator<entry>;
			using const_reverse_iterator = const_reverse_iterator<entry>;

			//We will keep the size of the table at power of 2 to avoid expensive modulus operation
			constexpr static auto     pow = xs::c_algo::log_2_int(Size) + 1; // we will overcompensate to ensure enough memory
			constexpr static uint64_t MAXSIZEPOW2 = xs::c_algo::integral_pow(2, pow);
			constexpr static uint64_t MAXSIZEPOW2MINUSONE = MAXSIZEPOW2 - 1;
		public:

			//The additional memory is used for metadata information
			// |----header----|------------value------------|
			hashmap_fixed()
				:p_entries{ new uint8_t[MAXSIZEPOW2 * sizeof(entry) + MAXSIZEPOW2] }
			{
			}

		private:
			
			uint8_t* p_entries;
			hashfunc m_hash;
		};
	}
}

#endif