#ifndef __XS_CSTRING__
#define __XS_CSTRING__
#include <iostream>
#include "../algorithms/xs_algorithms.h"
#include "../data_structures/xs_iterators.h"

namespace xs
{
	namespace ds
	{
		class cxstring
		{
			using iterator = iterator<char>;
			using const_iterator = const_iterator<char>;
			using reverse_iterator = reverse_iterator<char>;
			using const_reverse_iterator = const_reverse_iterator<char>;
			using pointer = char*;
			using reference = char&;
			using const_pointer = const char*;
			using const_reference = const char&;

		public:
			template <size_t N>
			constexpr cxstring(const char(&_str)[N])
				: cxstring{ _str, N }
			{}

			constexpr cxstring(const char* _str, size_t _length)
				: p_data{_str}, m_length{_length}, m_size{_length + 1}
			{}

			constexpr cxstring(const char* _begin, const char* _end)
				: cxstring{_begin, static_cast<size_t>(_end-_begin)}
			{
			}

			constexpr cxstring(const char* _begin)
				: cxstring{_begin, length(_begin)}
			{
			}

			static constexpr size_t length(const char* _begin)
			{
				return *_begin ? 1 + length(_begin + 1) : 0;
			}

			constexpr size_t length() const
			{
				return m_length;
			}

			constexpr size_t size() const
			{
				return m_size;
			}

			constexpr const_iterator begin() const
			{
				return const_iterator{ p_data };
			}

			constexpr const_iterator end() const
			{
				return const_iterator{ p_data + m_length + 1 };
			}

			constexpr const_iterator cbegin() const
			{
				return  const_iterator{ p_data };
			}

			constexpr const_iterator cend() const
			{
				return  const_iterator{ p_data + m_length + 1 };
			}

			constexpr const_reverse_iterator crbegin() const
			{
				return  const_reverse_iterator{ p_data };
			}

			constexpr const_reverse_iterator crend() const
			{
				return const_reverse_iterator{ p_data + m_length + 1 };
			}

			constexpr char operator[](size_t index) const
			{
				return *(p_data + index);
			}

			constexpr char operator()(size_t index) const
			{
				return *(p_data + index);
			}

			friend std::ostream& operator<<(std::ostream& os, const cxstring& string)
			{
				for (const char& c : string)
				{
					os << c;
				}

				return os;
			}

		private:

			const char* p_data;
			size_t m_length, m_size;
		};
	}
}


constexpr bool operator==(const xs::ds::cxstring& lhs, const xs::ds::cxstring& rhs)
{
	return xs::c_algo::is_equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

constexpr bool operator!=(const xs::ds::cxstring& lhs, const xs::ds::cxstring& rhs)
{
	return (lhs == rhs);
}

#endif