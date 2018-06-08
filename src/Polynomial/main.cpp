#include <iostream>

#include "Polynomial.hpp"

int main()
{
	Polynomial a{ { 1 , 2} }, b{ {0, 1} };
	a.print();
	b.print();
	
	(a * b).print();

	std::cout << a.eval(10);

	system("pause");
	return 0;
}