#include <ncurses.h>
#include <TOaNL/input.hpp>

int main(void)
{
    initscr();
    clear();
    noecho();
    cbreak();

	toanl::input input;

	input.on_mouse.attach([](int x, int y){
		wprintw(stdscr, "mouse: %d %d\n", x, y);
	}, false);

	input.on_keyboard.attach([](int ch){
		wprintw(stdscr, "key: %d\n", ch);
	}, false);

	input.unblock_loop();

	std::this_thread::sleep_for(std::chrono::seconds(30));

    endwin();
    return 0;
}

