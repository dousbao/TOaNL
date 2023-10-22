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

	std::vector<std::tuple<int, int, int>> points = {
		{ 10, 0, 0 }, { 0, 10, 0 }, { 7, 4, 0 }, { 10, 10, 0 }, { 15,4, 0 }, { 20, 8, 0 }
	};

	toanl::rasterizer raster;
	toanl::projector project;
	toanl::rotater rotate(points);

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

		for (auto c : cell)
			mvprintw(c.second, c.first, "#");

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
