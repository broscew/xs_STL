#pragma once
#include <type_traits>
#include <utility>

namespace xs
{
	namespace ds
	{
		template<typename ...T_Types>
		class tuple;

		namespace details
		{
			template <size_t index, typename T_TYPE, bool isEmpty = (std::is_empty_v<T_TYPE>&& std::is_final_v<T_TYPE>)>
			class tuple_leaf
			{
				using value_type = T_TYPE;
				using reference = T_TYPE&;
				using const_reference = const T_TYPE&;

			public:
				constexpr tuple_leaf() :value{} {};
				constexpr tuple_leaf(const tuple_leaf& _leaf) : value{ _leaf.get() } {};

				template<typename VAL_TYPE, std::enable_if_t<std::is_same_v<std::decay_t<VAL_TYPE>, T_TYPE>, bool> = true>
				constexpr tuple_leaf(VAL_TYPE&& _value) :value{ std::forward<VAL_TYPE>(_value) } {};

				[[nodiscard]] reference get()
				{
					return value;
				}

				[[nodiscard]] const_reference get() const
				{
					return value;
				}

			private:
				value_type value;
			};

			template<size_t index, typename T_TYPE>
			class tuple_leaf<index, T_TYPE, true> : private T_TYPE
			{
				using value_type = T_TYPE;
				using reference = T_TYPE&;
				using const_reference = const T_TYPE&;
			public:
				[[nodiscard]] reference get() noexcept
				{
					return static_cast<reference>(*this);
				}

				[[nodiscard]] const_reference get() const noexcept
				{
					return static_cast<const_reference>(*this);
				}

			private:
			};

			template<typename Index, typename ...T_TYPES>
			struct tuple_impl;

			template<size_t ... indices, typename ... T_TYPES>
			struct tuple_impl<std::index_sequence<indices...>, T_TYPES...> : tuple_leaf<indices, T_TYPES>...
			{
				tuple_impl()
					:tuple_leaf<indices, T_TYPES>{}...
				{}

				template <typename ... Args>
				tuple_impl(Args&& ... args)
					:tuple_leaf<indices, T_TYPES>{std::forward<Args>(args)}...
				{}
			};


			template<size_t index, typename T_TYPE, typename Tuple_Type>
			struct tuple_leaf_aux;

			template<size_t index, typename T_TYPE, typename ... Tails>
			struct tuple_leaf_aux<index, T_TYPE, tuple<T_TYPE, Tails...>>
			{
				using type = typename tuple_leaf<index, T_TYPE>;
			};

			template<size_t index, typename T_TYPE, typename Head, typename ... Tails>
			struct tuple_leaf_aux<index, T_TYPE, tuple<Head, Tails...>>
			{
				using type = typename tuple_leaf_aux<index + 1, T_TYPE, tuple<Tails...>>::type;
			};


			template<size_t index, typename T_TYPE>
			struct tuple_element;

			template<typename Head, typename ... Tails>
			struct tuple_element<0, tuple<Head, Tails...>>
			{
				using type = Head;
			};

			template<size_t index, typename Head, typename ... Tails>
			struct tuple_element<index, tuple<Head, Tails...>>
			{
				using type = typename tuple_element<index - 1, tuple<Tails...>>::type;
			};

			template<size_t index, typename ...Tails>
			struct tuple_element<index, tuple<Tails...>>
			{
				using type = typename tuple_element<index, tuple<Tails...>>::type;
			};

			template<size_t ...N, typename Tuple_Type, typename Lambda>
			void for_each_tuple_impl(Tuple_Type&& _tuple, Lambda&& _func, std::index_sequence<N...>)
			{
				((void)_func(_tuple.get<N>()), ...);
			}
		}

		template<typename>
		struct tuple_size;

		template<typename ... T_TYPES>
		struct tuple_size <tuple<T_TYPES...>> : std::integral_constant<size_t, sizeof...(T_TYPES)>
		{};


		template<typename Tuple_Type, typename Lambda>
		void for_each_tuple(Tuple_Type&& _tuple, Lambda&& _func)
		{
			details::for_each_tuple_impl(std::forward<Tuple_Type>(_tuple), std::forward<Lambda>(_func), std::make_index_sequence<tuple_size<std::remove_reference_t<Tuple_Type>>::value>());
		}


		template<typename ...T_TYPES>
		class tuple : public details::tuple_impl<std::make_index_sequence<sizeof...(T_TYPES)>, T_TYPES...>
		{
		public:
			template <typename ... Args>
			tuple(Args&& ... args)
				:details::tuple_impl<std::make_index_sequence<sizeof...(T_TYPES)>,T_TYPES...>{std::forward<Args>(args)... }
			{}

			template <size_t index>
			[[nodiscard]] constexpr inline typename details::tuple_element<index, tuple<T_TYPES...>>::type& get() noexcept
			{
				using type = typename details::tuple_element<index, tuple<T_TYPES...>>::type;
				return static_cast<details::tuple_leaf<index, type>& > (*this).get();
			}

			template<size_t index>
			[[nodiscard]] constexpr const typename details::tuple_element<index, tuple<T_TYPES...>>::type& cget() const noexcept
			{
				using type = typename details::tuple_element<index, tuple<T_TYPES...>>::type;
				return static_cast<const details::tuple_leaf<index, type>&>(*this).get();
			}

			template <size_t index>
			[[nodiscard]] constexpr const typename details::tuple_element<index, tuple<T_TYPES...>>::type& get() const noexcept
			{
				using type =  typename details::tuple_element<index, tuple<T_TYPES...>>::type;
				return static_cast<const details::tuple_leaf<index, type>&>(*this).get();
			}


			template <typename T_TYPE>
			[[nodiscard]] constexpr inline T_TYPE& get() noexcept
			{
				using type = typename details::tuple_leaf_aux<0, T_TYPE, tuple<T_TYPES...>>::type;
				return static_cast<type&>(*this).get();
			}

			template <typename T_TYPE>
			[[nodiscard]] constexpr inline const T_TYPE& cget() const noexcept
			{
				using type = typename details::tuple_leaf_aux<0, T_TYPE, tuple<T_TYPES...>>::type;
				return static_cast<const type&>(*this).get();
			}

			template <typename T_TYPE>
			[[nodiscard]] constexpr inline const T_TYPE& get() const noexcept
			{
				using type = typename details::tuple_leaf_aux<0, T_TYPE, tuple<T_TYPES...>>::type;
				return static_cast<const type&>(*this).get();
			}

			constexpr inline size_t size() const
			{
				return sizeof...(T_TYPES);
			}
		private:
		};

		template<>
		class tuple<>
		{
		public:
		private:
		};
	}
}