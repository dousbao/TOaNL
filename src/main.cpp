#include <ncurses.h>
#include <TOaNL/input.hpp>
#include <TOaNL/shader.hpp>
#include <TOaNL/signal.hpp>
#include <TOaNL/rotater.hpp>
#include <TOaNL/projector.hpp>
#include <TOaNL/rasterizer.hpp>

using namespace std::chrono_literals;

int main(void)
{
	initscr();
	cbreak();
	keypad(stdscr, true);
	noecho();
	refresh();

	std::vector<std::tuple<double, double, double>> points = {
		{ 40, 0, 0 }, { 25, 10, 0 }, { 10, 8, 0 }, { 22, 18, 0 }, { 17, 30, 0 }, { 28, 24, 0 }, { 40, 40, 0 },
		{ 52, 24, 0 }, { 63, 30, 0 }, { 58, 18, 0 }, { 70, 8, 0 }, { 55, 10, 0 }
	};

	toanl::rasterizer raster;
	toanl::projector project;
	toanl::rotater rotate(points);
	toanl::shader shade;
	toanl::input input;

	std::vector<std::pair<int, int>> point_2d;
	for (auto p : points) 
		point_2d.push_back(project(p));

	auto cells = raster(point_2d);
	auto darkness = shade(cells);

	for (int i = 0; i < cells.size(); ++i)
		mvaddch(cells[i].second, cells[i].first, toanl::shader::float2char(darkness[i]));

	refresh();

	input.on_mouse.attach([&](int x, int y){
		float radian = 0.15;

		for (int j = 0; j < 21; ++j) {
			std::vector<std::tuple<int, int, int>> points_rotate;
			for (auto p : points)
				points_rotate.push_back(rotate(p, radian));

			std::vector<std::pair<int, int>> point_2d;
			for (auto p : points_rotate) 
				point_2d.push_back(project(p));

			auto cells = raster(point_2d);
			auto darkness = shade(cells);

			for (int i = 0; i < cells.size(); ++i)
				mvaddch(cells[i].second, cells[i].first, toanl::shader::float2char(darkness[i]));

			refresh();
			std::this_thread::sleep_for(0.1s);
			clear();

			for (int i = 0; i < points.size(); ++i)
				points[i] = points_rotate[i];
		}

		std::vector<std::pair<int, int>> point_2d;
		for (auto p : points) 
			point_2d.push_back(project(p));

		auto cells = raster(point_2d);
		auto darkness = shade(cells);

		for (int i = 0; i < cells.size(); ++i)
			mvaddch(cells[i].second, cells[i].first, toanl::shader::float2char(darkness[i]));

		refresh();
	}, false);

	input.dead_loop();

	endwin();
	return 0;
}
