#ifndef __TOANL_SIGNAL_HPP__
#define __TOANL_SIGNAL_HPP__

#include <array>
#include <functional>
#include <cstdint>

namespace toanl {

template <std::int16_t MaxSize>
class signal {
public:
	using id = std::int16_t;
	using invocable = std::function<void(void)>;
	using subscriber = std::tuple<id, bool, invocable>;

public:
	signal(void) noexcept
	{
		for (auto &sub : _subscribers)
			std::get<id>(sub) = -1;
	}

	virtual ~signal(void) noexcept = 0;

public:
	template <typename Func>
	id attach(Func &&function, bool call_once = true)
	{
		int index = _next;

		if (std::get<id>(_subscribers[index]) != -1) {
			for (int i = 0; i < MaxSize; ++i)
				if (std::get<id>(_subscribers[i]) == -1) {
					index = i;
					break;
				}
			
			if (index == _next)
				return -1;
		}

		_subscribers[index] = std::make_tuple(index, call_once, std::forward<Func>(function));

		_next = index + 1 < MaxSize ? index + 1 : 0;
		return index;
	}

	void detach(id target) noexcept
	{
		std::get<id>(_subscribers[target]) = -1;
	}

	virtual void operator()(void)
	{
		for (const auto &sub : _subscribers) {
			auto &[id, call_once, func] = sub;

			if (id != -1) {
				func();
				if (call_once) 
					detach(id);
			}
		}
	}

private:
	std::uint8_t _next = 0;
	std::array<subscriber, MaxSize> _subscribers;
};

} // namespace toanl

#endif // __TOANL_SIGNAL_HPP__
