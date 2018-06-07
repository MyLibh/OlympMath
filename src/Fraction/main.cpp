#include <iostream>

#include "Fraction.hpp"

int main()
{
	Fraction a{ 1, 4 }, b{1, 4};

	std::cout << a + b << std::endl;

	system("pause");
	return 0;
}