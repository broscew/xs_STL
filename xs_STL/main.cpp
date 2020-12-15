#include <iostream>
#include "xs_stl/Algorithms/xs_sort.h"
#include "xs_stl/algorithms/xs_algorithms.h"
#include "xs_stl/data_structures/xs_cxarray.h"
#include "xs_stl/data_structures/xs_hashmap.h"
#include "xs_stl//utilities/xs_reflection.h"
#include "xs_stl/data_structures/xs_tuple.h"
#include <random>
#include <array>


struct point
{
	float x;
	float y;

	friend std::ostream& operator<<(std::ostream& os, const point& p)
	{
		os << p.x << ", " << p.y;

		return os;
	}
};

struct transform
{
	point position;
	point scale;
};

REFLECT_TYPE(point)
REFLECT_FIELD(x)
REFLECT_FIELD(y)
REFLECT_END

REFLECT_TYPE(transform)
REFLECT_FIELD(position)
REFLECT_FIELD(scale)
REFLECT_END

int main()
{
	xs::ds::tuple<int, double, float> my_tuple{ 1, 3.0, 4.5f };

	point p{ 1.2f, 2.f };

	auto descriptor = xs::reflect::type<point>();
	descriptor.print_info(p);

	descriptor.set_field(p, "y", 1337.f);

	descriptor.print_info(p);

	transform t{ point{42.f, 52.f}, point{128.f, 314.f} };

	xs::reflect::type_descriptor<transform> transform_desc = xs::reflect::type<transform>();
	transform_desc.set_field(t, "scale", point{ 130013,789 });

	transform_desc.print_info(t);

	xs::ds::cxstring test_string{ "Hello_World" };

	for (auto c : test_string)
	{
		std::cout << c << ", ";
	}

	constexpr xs::ds::cxarray<int, 4> constexpr_array1{ 1,2,3,4 };
	constexpr xs::ds::cxarray<int, 4> constexpr_array2{ 1,2,3,4 };

	static_assert(constexpr_array1 == constexpr_array2);

	return 0;
}