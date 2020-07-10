#include "lib_test.h"

#include <iostream>

Demo::Demo(int x): a(x) {}

void Demo::print_data()
{
	std::cout << a << std::endl;
}

