#ifndef  __XS_SORT_
#define __XS_SORT__

namespace xs
{
	namespace algo
	{
		namespace detail
		{
			template <typename Count_Type, typename Itr_In, typename Itr_Out, typename ExtractKey>
			void counting_sort_impl(Itr_In in_begin, Itr_In in_end, Itr_Out out_begin, ExtractKey&& extract_key)
			{
				Count_Type counts[256] = { 0 };
				Count_Type total = 0;

				for (auto itr = in_begin; itr != in_end; ++itr)
				{
					++counts[extract_key(*itr)];
				}

				for (Count_Type& count : counts)
				{
					Count_Type old_count = count;
					count = total;
					total += old_count;
				}

				for (auto itr = in_begin; itr != in_end; ++itr)
				{
					auto key = extract_key(*itr);
					out_begin[counts[key]++] = std::move(*itr);
				}
			}

			template <typename Itr_In, typename Itr_Out, typename ExtractKey>
			void counting_sort_impl(Itr_In in_begin, Itr_In in_end, Itr_Out out_begin, ExtractKey&& extract_key)
			{
				counting_sort_impl<uint64_t>(in_begin, in_end, out_begin, extract_key);
			}

			inline bool convert_bytes(bool val)
			{
				return val;
			}

			inline uint8_t convert_bytes(uint8_t val)
			{
				return val;
			}

			inline int8_t convert_bytes(int8_t val)
			{
				return static_cast<int8_t>(val) + 128;
			}



			template<size_t>
			struct radix_sorter_impl;

			template<>
			struct radix_sorter_impl<1>
			{
				template <typename Itr_In, typename Itr_Out, typename ExtractKey>
				bool sort(Itr_In in_begin, Itr_In in_end, Itr_Out out_begin, ExtractKey&& extract_key)
				{
					counting_sort_impl(in_begin, in_end, out_begin, [&](auto&& val)
					{
						return convert_bytes(val);
					});

					return true;
				}
			};


			template <typename T_TYPE>
			struct radix_sorter;

			template<>
			struct radix_sorter<uint8_t> : radix_sorter_impl<sizeof(uint8_t)>
			{

			};

			template<>
			struct radix_sorter<int8_t> : radix_sorter_impl<sizeof(int8_t)>
			{

			};
		}

		void counting_sort(uint8_t* in_begin, uint8_t* in_end)
		{
			size_t counts[256] = {0};
			size_t prefix[256] = {0};
			size_t total = {};

			for (uint8_t* itr = in_begin; itr != in_end; ++itr)
			{
				++counts[*itr];
			}

			for (size_t i = 0; i < 256; ++i)
			{
				size_t old_count = counts[i];
				counts[i] = total;
				total += old_count;
				prefix[i] = total;

			}



		}
	}
}

#endif // ! __XS_ALGORITHMS__
