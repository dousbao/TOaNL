#include <ncurses.h>
#include <TOaNL/shader.hpp>
#include <TOaNL/rasterizer.hpp>

int main(void)
{
	initscr();
	noecho();
	cbreak();

	toanl::rasterizer raster;
	std::vector<std::pair<int, int>> points = {
		{ 1, 1 }, { 5, 1 }, {2, 4}
	};

	int ch;

	do {
		clear();
		refresh();

		auto cell = raster(points);

		for (auto point : cell)
			mvprintw(point.second, point.first, "X");
	} while ((ch = getch()) != 'q');


	endwin();
	return 0;
}
