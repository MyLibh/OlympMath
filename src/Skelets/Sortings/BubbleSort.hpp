#include <utility> // std::iter_swap
#include <xstddef> // std::less


template<typename Iterator, typename Predicate = std::less<>>
void BubbleSort(Iterator first, Iterator last, Predicate predicate = Predicate())
{
	while (first < --last)
		for (auto i{ first }; i < last; ++i)
			if (predicate(*(i + 1), *i))
				std::iter_swap(i, i + 1);
}
