#include <utility> // std::iter_swap
#include <xstddef> // std::less

template <typename Iterator, typename Predicate = std::less<>>
void InsertionSort(Iterator first, Iterator last, Predicate pred = Predicate())
{
	for (Iterator i{ first + 1 }; i != last; ++i)
		for (Iterator j{ i }; j != first && pred(*j, *(j - 1)); --j)
			std::iter_swap(j - 1, j);
}