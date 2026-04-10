#include <iostream>
#include "xor_list.hpp"

int main()
{
	xor_list<int> xList;

	for (int i = 0; i < 10; ++i)
		xList.push_front(i);

	for (const int value : xList)
		std::cout << value;
}
