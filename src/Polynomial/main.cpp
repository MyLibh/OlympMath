#include <iostream>

#include "Polynomial.hpp"

int main()
{
	Polynomial a{ { 1 , 2} }, b{ {0, 1, 6} };
	a.print();
	b.print();
	
	(a * b).print();

	b.dir().print();

	system("pause");
	return 0;
}