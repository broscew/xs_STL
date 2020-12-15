#pragma once
#include <tuple>
#include <iomanip>
#include "../data_structures/xs_cxstring.h"
#include "../utilities/xs_assert.h"
#include "../data_structures/xs_tuple.h"

namespace xs
{
	namespace reflect
	{
		template <typename T_TYPE>
		struct type_info;

		namespace details
		{
			template<typename T_TYPE, size_t ...N>
			xs::ds::tuple <typename reflect::type_info<T_TYPE>::template member_info<N>...> enumerate_members(std::index_sequence<N...>);


			template<typename tuple_type, size_t ... indices>
			constexpr bool is_fieldname_valid_impl(ds::cxstring _fieldname, tuple_type&& _tuple, std::index_sequence<indices...>)
			{
				return (((_fieldname == _tuple.get<indices>().name)+ ...));
			}

			template<typename tuple_type>
			constexpr bool is_fieldname_valid(ds::cxstring _fieldname, tuple_type&& _tuple)
			{
				return is_fieldname_valid_impl(_fieldname, std::forward<tuple_type>(_tuple), std::make_index_sequence<ds::tuple_size<std::remove_reference_t<tuple_type>>::value>{});
			}
		}

		template<typename T_TYPE>
		using member_list = decltype(details::enumerate_members<T_TYPE>(std::make_index_sequence<type_info<T_TYPE>::member_count>{}));


		template<typename T_TYPE>
		struct type_descriptor
		{
			using my_type = T_TYPE;
			using my_info = type_info<T_TYPE>;

			void print_info(my_type& _obj)
			{
#ifdef _DEBUG
				std::cout << std::setw(4) << type_info<my_type>::name << '\n';
				std::cout << std::setw(5) << "{\n";
				for_each([&](auto member)
				{
					std::cout << std::setw(8) << member.name << " = " << member(_obj) << ";\n";
				});
				std::cout << std::setw(6) << "};\n"<<std::endl;
#endif
			}

			template<typename lambda>
			void for_each(lambda&& _func)
			{
				xs::ds::for_each_tuple(members, _func);
			}

			template<typename object_type, typename value_type>
			constexpr void set_field(object_type&& _obj, ds::cxstring _fieldname, value_type&& _value)
			{
#ifdef _DEBUG
				xsassert(details::is_fieldname_valid(_fieldname, members), "Invalid Fieldname!");
#endif
				set_field_impl(std::forward<object_type>(_obj), _fieldname, std::forward<value_type>(_value), std::make_index_sequence<ds::tuple_size< member_list<my_type>>::value>{});
			}

			member_list<my_type> members;

		private:
			template<typename object_type, typename value_type, size_t ... indices>
			constexpr void set_field_impl(object_type&& _obj,  ds::cxstring _fieldname, value_type&& _value, std::index_sequence<indices...>)
			{
				((members.get<indices>()(_obj) = (members.get<indices>().name == _fieldname) ? std::forward<value_type>(_value) : std::move(members.get<indices>()(_obj))),...);
			}
		};

		template<typename T_TYPE>
		type_descriptor<T_TYPE> type()
		{
			return type_descriptor<T_TYPE>{};
		}
	}
}

#define REFLECT_TYPE(TYPE) \
template <> \
struct xs::reflect::type_info<TYPE> \
{ \
	using my_type = TYPE; \
    static constexpr xs::ds::cxstring name {#TYPE}; \
	template<size_t> struct member_info; \
	static constexpr size_t member_index_offset = __COUNTER__ + 1;

#define REFLECT_FIELD(FieldName) \
	template<> struct member_info<__COUNTER__ - member_index_offset> \
	{ \
		using member_type = decltype(my_type::FieldName); \
		static constexpr xs::ds::cxstring name {#FieldName}; \
        static constexpr size_t offset = offsetof(my_type, FieldName); \
		[[nodiscard]] member_type& operator() (my_type& object) noexcept \
		{ \
			return *(reinterpret_cast<member_type*>(reinterpret_cast<char*>(&object) + offset)); \
		} \
    };

#define REFLECT_END\
	static constexpr size_t member_count = __COUNTER__ - member_index_offset; \
};