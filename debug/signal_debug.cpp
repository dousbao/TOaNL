#include <iostream>
#include <TOaNL/signal.hpp>

void print(int i)
{
	std::cout << i << __PRETTY_FUNCTION__ << std::endl;
}

int main(void)
{
	toanl::signal<void(int), 16> on_debug;

	int i = on_debug.attach(print, false);
	std::cout << on_debug.attach(print) << std::endl;
	std::cout << on_debug.attach(print) << std::endl;
	std::cout << i << std::endl;

	on_debug(5);

	on_debug.detach(i);

	on_debug(2);
}
