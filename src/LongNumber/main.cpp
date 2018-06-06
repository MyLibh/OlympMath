#include "LongNumber.hpp"

typedef LongNumber LNUM;

int main()
{
	LNUM a(1), b(1);
	a.print();
	b.print();

	(a - b).print();

	system("pause");
	return 0;
}