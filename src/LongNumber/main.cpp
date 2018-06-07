#include <iostream>
#include <string>

#include "LongNumber.hpp"

typedef LongNumber LNUM;

void test()
{
	using namespace std;

	LNUM a(-25),
		 b(-25);
	a.print();
	b.print();

	(a * b).print(); 
}

int main()
{
	test();

	system("pause");
	return 0;
}

