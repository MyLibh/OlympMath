#include <iostream>

#include "Polynomial.hpp"

int main()
{
	Polynomial a{ { 1, 2, 3 } }, b{ { 0, 1 } }, c{ { 0, 1, 2, 3 } };
	a.print();
	b.print();
	
	(a * b).print();
	(c / b).print();

	b.dir().print();

	system("pause");
	return 0;
}