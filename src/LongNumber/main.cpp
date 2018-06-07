#include <iostream>
#include <string>

#include "LongNumber.hpp"

void test()
{
	using namespace std;

	LNUM a(-2),
		 b(3);
	a.print();
	b.print();
	a.factorial().print();
	a.power(b).print(); 
}

int main()
{
	test();

	system("pause");
	return 0;
}

