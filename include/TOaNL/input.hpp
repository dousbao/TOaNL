#ifndef __TOANL_INPUT_HPP__
#define __TOANL_INPUT_HPP__

#include <ncurses.h>
#include <TOaNL/signal.hpp>
#include <thread>

namespace toanl {

class input {
public:
	explicit input(const mmask_t &mask = ALL_MOUSE_EVENTS) noexcept
	{
		keypad(stdscr, TRUE);
		mousemask(mask, nullptr);
	}

public:
	void unblock_loop(void)
	{
		std::thread([this](){
			while (true) {
				int ch = getch();

				switch (ch) {
					case KEY_MOUSE:
						MEVENT event;
						if (getmouse(&event) == OK)
							on_mouse(event.x, event.y);
						break;
					default:
						on_keyboard(ch);
				}
			}
		}).detach();
	}

public:
	signal<void(int, int), 128> on_mouse;
	signal<void(int), 128> on_keyboard;
};

} // namespace toanl

#endif // __TOANL_INPUT_HPP__
