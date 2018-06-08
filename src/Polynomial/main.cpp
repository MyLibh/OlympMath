#include <iostream>

#include "Polynomial.hpp"

int main()
{
	Polynomial a{ { 1 , 1, 3 } }, b{ {0, 1} };
	a.print();
	b.print();
	
	(a * b).print();

	system("pause");
	return 0;
}