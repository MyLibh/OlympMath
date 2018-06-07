#include <iostream>
#include <string>

#include "LongNumber.hpp"

typedef LongNumber LNUM;

void test()
{
	using namespace std;

	LNUM a(15),
		 b(10);
	a.print();
	b.print();
	a.factorial().print();
	(a | b).print(); 
}

int main()
{
	test();

	system("pause");
	return 0;
}

