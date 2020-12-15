#ifndef __XS_CXARRAY__
#define __XS_CXARRAY__
#include <cassert>    //assert
#include "../data_structures/xs_iterators.h"
#pragma warning(push)
#pragma warning(disable:6385)

namespace xs
{
	namespace ds
	{
		template<typename T, size_t Size>
		class cxarray
		{
		public:
			using iterator = iterator<T>;
			using const_iterator = const_iterator<T>;
			using reverse_iterator = reverse_iterator<T>;
			using const_reverse_iterator = const_reverse_iterator<T>;
			using pointer = T*;
			using reference = T&;
			using const_pointer = const T*;
			using const_reference = const T&;



			constexpr void fill(T value)
			{
				xs::c_algo::fill_n<Size>(std::move(value));
			}

			constexpr size_t length() const
			{
				return Size;
			}

			constexpr bool empty() const
			{
				return false;
			}

			constexpr size_t size() const
			{
				return Size;
			}

			constexpr size_t max_size() const
			{
				return Size;
			}

			[[nodiscard]] constexpr iterator begin()
			{
				return iterator{ p_data };
			}

			[[nodiscard]] constexpr const_iterator begin() const
			{
				return const_iterator{ p_data };
			}

			[[nodiscard]] constexpr iterator end()
			{
				return iterator{ p_data + Size };
			}

			[[nodiscard]] constexpr const_iterator end() const
			{
				return const_iterator{ p_data + Size };
			}

			[[nodiscard]] constexpr const_iterator cbegin() const
			{
				return const_iterator{ p_data };
			}

			[[nodiscard]] constexpr const_iterator cend() const
			{
				return const_iterator{ p_data + Size };
			}

			[[nodiscard]] constexpr reverse_iterator rbegin()
			{
				return reverse_iterator{ p_data + (Size - 1) };
			}

			[[nodiscard]] constexpr const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator{ p_data + (Size - 1) };
			}

			[[nodiscard]] constexpr reverse_iterator rend()
			{
				return reverse_iterator{ p_data - 1 };
			}

			[[nodiscard]] constexpr const_reverse_iterator rend() const
			{
				return const_reverse_iterator{ p_data - 1 };
			}

			[[nodiscard]] constexpr const_reverse_iterator crbegin() const
			{
				return const_reverse_iterator{ p_data + (Size - 1) };
			}

			[[nodiscard]] constexpr const_reverse_iterator crend() const
			{
				return const_reverse_iterator{ p_data - 1 };
			}

			constexpr reference front()
			{
				return p_data[0];
			}

			constexpr const_reference front() const
			{
				return p_data[0];
			}

			constexpr reference back()
			{
				return p_data[Size - 1];
			}

			constexpr const_reference back() const
			{
				return p_data[Size - 1];
			}

			[[nodiscard]] constexpr reference at(size_t index)
			{
#ifdef _DEBUG
				if (index >= Size)
					throw std::out_of_range("index out of range!");
#endif
				return p_data[index];
			}

			[[nodiscard]] constexpr const_reference at(size_t index) const
			{
#ifdef _DEBUG
				if (index >= Size)
					throw std::out_of_range("index out of range!");
#endif
				return p_data[index];
			}

			constexpr reference operator[](size_t index)
			{
				assert(index < Size);
				return p_data[index];
			}

			constexpr const_reference operator[](size_t index) const
			{
				assert(index < Size);
				return p_data[index];
			}

			constexpr pointer data()
			{
				return p_data;
			}

			constexpr const_pointer data() const
			{
				return p_data;
			}

			T p_data[Size];
		};

		//This is a specialized version meant to handle the case
	//when the size of the array is set to 0
	//Main takeaway from this portion is that the iterator 
	//return from an array with size 0 will be a nullptr
		template <typename T>
		class cxarray <T, 0>
		{
		public:
			using iterator = iterator<T>;
			using const_iterator = const_iterator<T>;
			using reverse_iterator = reverse_iterator<T>;
			using const_reverse_iterator = const_reverse_iterator<T>;
			using pointer = T*;
			using reference = T&;
			using const_pointer = const T*;
			using const_reference = const T&;

			constexpr void fill([[maybe_unused]] const T& value)
			{
			}

			constexpr void swap([[maybe_unused]] const cxarray<T, 0>& value)
			{
			}

			constexpr size_t length() const
			{
				return 0;
			}

			constexpr bool empty() const
			{
				return true;
			}

			constexpr size_t size() const
			{
				return 0;
			}

			constexpr size_t max_size() const
			{
				return 0;
			}

			[[nodiscard]] constexpr iterator begin()
			{
				return iterator{ nullptr };
			}

			[[nodiscard]] constexpr const_iterator begin() const
			{
				return const_iterator{ nullptr };
			}

			[[nodiscard]] constexpr iterator end()
			{
				return iterator{ nullptr };
			}

			[[nodiscard]] constexpr const_iterator end() const
			{
				return const_iterator{ nullptr };
			}

			[[nodiscard]] constexpr const_iterator cbegin() const
			{
				return const_iterator{ nullptr };
			}

			[[nodiscard]] constexpr const_iterator cend() const
			{
				return const_iterator{ nullptr };
			}


			[[nodiscard]] constexpr reverse_iterator rbegin()
			{
				return reverse_iterator{ nullptr };
			}

			[[nodiscard]] constexpr const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator{ nullptr };
			}
			[[nodiscard]] constexpr reverse_iterator rend()
			{
				return reverse_iterator{ nullptr };
			}

			[[nodiscard]] constexpr const_reverse_iterator rend() const
			{
				return const_reverse_iterator{ nullptr };
			}

			[[nodiscard]] constexpr const_reverse_iterator crbegin() const
			{
				return const_reverse_iterator{ nullptr };
			}

			[[nodiscard]] constexpr const_reverse_iterator crend() const
			{
				return const_reverse_iterator{ nullptr };
			}

			constexpr reference front()
			{
				return p_data[0];
			}

			constexpr const_reference front() const
			{
				return p_data[0];
			}

			constexpr reference back()
			{
				return p_data[0];
			}

			constexpr const_reference back() const
			{
				return p_data[0];
			}

			[[nodiscard]] constexpr reference at(size_t index)
			{
#ifdef _DEBUG
				if (index >= 0)
					throw std::out_of_range("index out of range!");
#endif
				return p_data[index];
			}

			[[nodiscard]] constexpr const_reference at(size_t index) const
			{
#ifdef _DEBUG
				if (index >= 0)
					throw std::out_of_range("index out of range!");
#endif
				return p_data[index];
			}

			constexpr reference operator[](size_t index)
			{
				return p_data[index];
			}

			constexpr const_reference operator[](size_t index) const
			{
				return p_data[index];
			}

			constexpr pointer data()
			{
				return nullptr;
			}

			constexpr const_pointer data() const
			{
				return nullptr;
			}

			T p_data[1];
		};
	}
}

template<typename T_TYPE, size_t Size>
constexpr bool operator==(const xs::ds::cxarray<T_TYPE, Size>& lhs, const xs::ds::cxarray<T_TYPE, Size>& rhs)
{
	return xs::c_algo::is_equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
#pragma warning(pop)
#endif