#include <ncurses.h>
#include <chrono>
#include <thread>
#include <TOaNL/rotater.hpp>
#include <TOaNL/shader.hpp>
#include <TOaNL/projector.hpp>
#include <TOaNL/rasterizer.hpp>

using namespace std::chrono_literals;

int main(void)
{
	initscr();
	cbreak();
	noecho();
	refresh();
	
	// start_color();

	// if (!has_colors())
	// 	throw std::runtime_error("current terminal does not support rgb color");
	//
	// if (init_color(8, 188, 218, 172) == ERR) return -1;
	// init_color(9, 277, 328, 249);
	// init_color(10, 448, 558, 390);
	// init_color(11, 514, 675, 425);
	// init_color(12, 667, 866, 554);
	//
	// if (init_pair(1, COLOR_WHITE, 8) == ERR) return -1;
	// init_pair(2, COLOR_WHITE, 9);
	// init_pair(3, COLOR_WHITE, 10);
	// init_pair(4, COLOR_WHITE, 11);
	// init_pair(5, COLOR_WHITE, 12);
	//
	// attron(COLOR_PAIR(5));
	// mvprintw(10, 10, "Hello, world");
	// attroff(COLOR_PAIR(5));

	std::vector<std::tuple<int, int, int>> points = {
		// { 10, 0, 0 }, { 0, 10, 0 }, { 7, 4, 0 }, { 10, 10, 0 }, { 15,4, 0 }, { 20, 8, 0 }
		{ 8, 13, 0 }, { 18, 11, 0 }, { 27, 3, 0 }, { 38, 3, 0 }, { 36, 19, 0 }, { 37, 26, 0 }, { 28, 26, 0 }, { 19, 17, 0 }
	};

	toanl::rasterizer raster;
	toanl::projector project;
	toanl::rotater rotate(points);
	toanl::shader shade;

	float radian = 0.5;
	while (true) {
		wprintw(stdscr, "%d %d\n", LINES, COLS);

		std::vector<std::tuple<int, int, int>> rotate_points;
		for (auto p : points)
			rotate_points.push_back(rotate(p, radian));

		std::vector<std::pair<int, int>> point_2ds;
		for (auto p : rotate_points) 
			point_2ds.push_back(project(p));

		auto cell = raster(point_2ds);

		auto darks = shade(cell);

		for (int i = 0; i < cell.size(); ++i) {
			mvprintw(cell[i].second, cell[i].first, "%c", toanl::shader::float2char(darks[i]));
		}
		// for (auto c : cell)
			// mvprintw(c.second, c.first, "#");

		refresh();
		std::this_thread::sleep_for(0.1s);
		clear();
		refresh();

		for (int i = 0; i < points.size(); ++i)
			points[i] = rotate_points[i];
	}

	endwin();
	return 0;
}
