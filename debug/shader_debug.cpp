#include <iostream>
#include <ncurses.h>
#include <TOaNL/shader.hpp>
#include <TOaNL/rasterizer.hpp>

int main(void)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::geometric_distribution<int> dist(0.5);

	std::cout << dist.max() << " " << dist.min() << std::endl;

	return 0;
}
