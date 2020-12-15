#pragma once
#include <iterator>

namespace xs
{
	namespace ds
	{
		template <typename T>
		class iterator
		{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using iterator_category = std::random_access_iterator_tag;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			constexpr iterator(T* ptr)
				:m_ptr{ ptr }
			{}

			iterator() = default;
			iterator(const iterator&) = default;
			iterator(iterator&&) = default;

			iterator& operator= (const iterator&) = default;
			iterator& operator= (iterator&&) = default;

			constexpr reference operator*()
			{
				return *(m_ptr);
			}

			constexpr pointer operator->()
			{
				return m_ptr;
			}

			constexpr iterator operator++()
			{
				iterator tmp = *this;
				++m_ptr;
				return tmp;
			}

			constexpr iterator operator++(int)
			{
				iterator tmp = *this;
				++m_ptr;
				return tmp;
			}

			constexpr iterator operator--()
			{
				iterator tmp = *this;
				--m_ptr;
				return tmp;
			}

			constexpr iterator operator--(int)
			{
				iterator tmp = *this;
				--m_ptr;
				return tmp;
			}

			constexpr iterator& operator+=(ptrdiff_t offset)
			{
				m_ptr += offset;
				return *this;
			}

			constexpr iterator& operator-=(ptrdiff_t offset)
			{
				m_ptr -= offset;
				return *this;
			}

			constexpr iterator operator+(ptrdiff_t offset)
			{
				return iterator{ m_ptr + offset };
			}

			constexpr iterator operator-(ptrdiff_t offset)
			{
				return iterator{ m_ptr - offset };
			}

			constexpr ptrdiff_t operator-(const iterator& rhs)
			{
				return m_ptr - rhs.m_ptr;
			}

			constexpr reference operator[](size_t index)
			{
				return m_ptr[index];
			}

			constexpr bool operator== (const iterator& rhs) const
			{
				return m_ptr == rhs.m_ptr;
			}

			constexpr bool operator!= (const iterator& rhs) const
			{
				return m_ptr != rhs.m_ptr;
			}

			constexpr bool operator< (const iterator& rhs) const
			{
				return m_ptr < rhs.m_ptr;
			}

			constexpr bool operator<= (const iterator& rhs) const
			{
				return m_ptr <= rhs.m_ptr;
			}

			constexpr bool operator> (const iterator& rhs) const
			{
				return m_ptr > rhs.m_ptr;
			}

			constexpr bool operator>= (const iterator& rhs) const
			{
				return m_ptr >= rhs.m_ptr;
			}

		private:
			pointer m_ptr;
		};

		template <typename T>
		class const_iterator
		{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = T;
			using difference_type = ptrdiff_t;
			using pointer = const T*;
			using reference = const T&;

			constexpr const_iterator(const T* ptr)
				:m_ptr{ ptr }
			{}

			const_iterator() = default;
			const_iterator(const const_iterator&) = default;
			const_iterator(const_iterator&&) = default;
			const_iterator& operator= (const const_iterator&) = default;
			const_iterator& operator= (const_iterator&&) = default;

			constexpr reference operator*() const
			{
				return *(m_ptr);
			}

			constexpr pointer operator->() const
			{
				return m_ptr;
			}

			constexpr const_iterator operator++()
			{
				const_iterator tmp = *this;
				++m_ptr;
				return tmp;
			}

			constexpr const_iterator operator++(int)
			{
				const_iterator tmp = *this;
				++m_ptr;
				return tmp;
			}

			constexpr const_iterator operator--()
			{
				const_iterator tmp = *this;
				--m_ptr;
				return tmp;
			}

			constexpr const_iterator operator--(int)
			{
				const_iterator tmp = *this;
				--m_ptr;
				return tmp;
			}

			constexpr const_iterator& operator+=(ptrdiff_t offset)
			{
				m_ptr += offset;
				return *this;
			}

			constexpr const_iterator& operator-=(ptrdiff_t offset)
			{
				m_ptr -= offset;
				return *this;
			}

			constexpr const_iterator operator+(ptrdiff_t offset) const
			{
				return const_iterator{ m_ptr + offset };
			}

			constexpr const_iterator operator-(ptrdiff_t offset) const
			{
				return const_iterator{ m_ptr - offset };
			}

			constexpr ptrdiff_t operator-(const const_iterator& rhs) const
			{
				return m_ptr - rhs.m_ptr;
			}

			constexpr reference operator[](size_t index) const
			{
				return m_ptr[index];
			}

			constexpr bool operator== (const const_iterator& rhs) const
			{
				return m_ptr == rhs.m_ptr;
			}

			constexpr bool operator!= (const const_iterator& rhs) const
			{
				return m_ptr != rhs.m_ptr;
			}

			constexpr bool operator< (const const_iterator& rhs) const
			{
				return m_ptr < rhs.m_ptr;
			}

			constexpr bool operator<= (const const_iterator& rhs) const
			{
				return m_ptr <= rhs.m_ptr;
			}

			constexpr bool operator> (const const_iterator& rhs) const
			{
				return m_ptr > rhs.m_ptr;
			}

			constexpr bool operator>= (const const_iterator& rhs) const
			{
				return m_ptr >= rhs.m_ptr;
			}

		private:
			pointer m_ptr;
		};

		//This is a simple modifiable array iterator
		//Size is use for debug purposes
		template <typename T>
		class reverse_iterator
		{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = T;
			using difference_type = ptrdiff_t;
			using pointer = T*;
			using reference = T&;

			constexpr reverse_iterator(T* ptr)
				:m_ptr{ ptr }
			{}

			reverse_iterator() = default;
			reverse_iterator(const reverse_iterator&) = default;
			reverse_iterator(reverse_iterator&&) = default;
			reverse_iterator& operator= (const reverse_iterator&) = default;
			reverse_iterator& operator= (reverse_iterator&&) = default;

			constexpr reference operator*()
			{
				return *(m_ptr);
			}

			constexpr pointer operator->()
			{
				return m_ptr;
			}

			constexpr reverse_iterator operator++()
			{
				reverse_iterator tmp = *this;
				--m_ptr;
				return tmp;
			}

			constexpr reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				--m_ptr;
				return tmp;
			}

			constexpr reverse_iterator operator--()
			{
				reverse_iterator tmp = *this;
				++m_ptr;
				return tmp;
			}

			constexpr reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				++m_ptr;
				return tmp;
			}

			constexpr reverse_iterator& operator+=(ptrdiff_t offset)
			{
				m_ptr -= offset;
				return *this;
			}

			constexpr reverse_iterator& operator-=(ptrdiff_t offset)
			{
				m_ptr += offset;
				return *this;
			}

			constexpr reverse_iterator operator+(ptrdiff_t offset)
			{
				return reverse_iterator{ m_ptr - offset };
			}

			constexpr reverse_iterator operator-(ptrdiff_t offset)
			{
				return reverse_iterator{ m_ptr + offset };
			}

			constexpr ptrdiff_t operator-(const reverse_iterator& rhs)
			{
				return rhs.m_ptr - m_ptr;
			}

			constexpr reference operator[](size_t index)
			{
				return m_ptr[index];
			}

			constexpr bool operator== (const reverse_iterator& rhs) const
			{
				return m_ptr == rhs.m_ptr;
			}

			constexpr bool operator!= (const reverse_iterator& rhs) const
			{
				return m_ptr != rhs.m_ptr;
			}

			constexpr bool operator< (const reverse_iterator& rhs) const
			{
				return m_ptr < rhs.m_ptr;
			}

			constexpr bool operator<= (const reverse_iterator& rhs) const
			{
				return m_ptr <= rhs.m_ptr;
			}

			constexpr bool operator> (const reverse_iterator& rhs) const
			{
				return m_ptr > rhs.m_ptr;
			}

			constexpr bool operator>= (const reverse_iterator& rhs) const
			{
				return m_ptr >= rhs.m_ptr;
			}

		private:
			pointer m_ptr;
		};


		//This is a simple read-only array iterator
		//Size is use for debug purposes
		template <typename T>
		class const_reverse_iterator
		{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = T;
			using difference_type = ptrdiff_t;
			using pointer = const T*;
			using reference = const T&;

			constexpr const_reverse_iterator(const T* ptr)
				:m_ptr{ ptr }
			{}

			const_reverse_iterator() = default;
			const_reverse_iterator(const const_reverse_iterator&) = default;
			const_reverse_iterator(const_reverse_iterator&&) = default;
			const_reverse_iterator& operator= (const const_reverse_iterator&) = default;
			const_reverse_iterator& operator= (const_reverse_iterator&&) = default;

			constexpr reference operator*() const
			{
				return *(m_ptr);
			}

			constexpr pointer operator->() const
			{
				return m_ptr;
			}

			constexpr const_reverse_iterator operator++()
			{
				const_reverse_iterator tmp = *this;
				--m_ptr;
				return tmp;
			}

			constexpr const_reverse_iterator operator++(int)
			{
				const_reverse_iterator tmp = *this;
				--m_ptr;
				return tmp;
			}

			constexpr const_reverse_iterator operator--()
			{
				const_reverse_iterator tmp = *this;
				++m_ptr;
				return tmp;
			}

			constexpr const_reverse_iterator operator--(int)
			{
				const_iterator tmp = *this;
				++m_ptr;
				return tmp;
			}

			constexpr const_reverse_iterator& operator+=(ptrdiff_t offset)
			{
				m_ptr -= offset;
				return *this;
			}

			constexpr const_reverse_iterator& operator-=(ptrdiff_t offset)
			{
				m_ptr += offset;
				return *this;
			}

			constexpr const_reverse_iterator operator+(ptrdiff_t offset) const
			{
				return const_reverse_iterator{ m_ptr - offset };
			}

			constexpr const_reverse_iterator operator-(ptrdiff_t offset) const
			{
				return const_reverse_iterator{ m_ptr + offset };
			}

			constexpr ptrdiff_t operator-(const const_reverse_iterator& rhs) const
			{
				return rhs.m_ptr - m_ptr;
			}

			constexpr reference operator[](size_t index) const
			{
				return m_ptr[index];
			}

			constexpr bool operator== (const const_reverse_iterator& rhs) const
			{
				return m_ptr == rhs.m_ptr;
			}

			constexpr bool operator!= (const const_reverse_iterator& rhs) const
			{
				return m_ptr != rhs.m_ptr;
			}

			constexpr bool operator< (const const_reverse_iterator& rhs) const
			{
				return m_ptr < rhs.m_ptr;
			}

			constexpr bool operator<= (const const_reverse_iterator& rhs) const
			{
				return m_ptr <= rhs.m_ptr;
			}

			constexpr bool operator> (const const_reverse_iterator& rhs) const
			{
				return m_ptr > rhs.m_ptr;
			}

			constexpr bool operator>= (const const_reverse_iterator& rhs) const
			{
				return m_ptr >= rhs.m_ptr;
			}

		private:
			pointer m_ptr;
		};
	}
}