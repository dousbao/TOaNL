#ifndef __TOANL_SIGNAL_HPP__
#define __TOANL_SIGNAL_HPP__

#include <array>
#include <functional>
#include <cstdint>
#include <mutex>

namespace toanl {

template <typename Signature, std::int16_t MaxSize>
class signal {
public:
	using id = std::int16_t;
	using invocable = std::function<Signature>;
	using subscriber = std::tuple<id, bool, invocable>;

public:
	signal(void) noexcept
	{
		for (auto &sub : _subscribers)
			std::get<id>(sub) = -1;
	}

public:
	template <typename Func>
	id attach(Func &&function, bool call_once = true)
	{
		std::unique_lock lock(_mt);

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
		std::unique_lock lock(_mt);

		_detach(target);
	}

	template <typename... Args>
	void operator()(Args... args)
	{
		std::unique_lock lock(_mt);

		for (const auto &sub : _subscribers) {
			auto &[id, call_once, func] = sub;

			if (id != -1) {
				func(args...);
				if (call_once) 
					_detach(id);
			}
		}
	}

private:
	void _detach(id target) noexcept
	{
		std::get<id>(_subscribers[target]) = -1;
	}

private:
	std::uint8_t _next = 0;
	std::mutex _mt;
	std::array<subscriber, MaxSize> _subscribers;
};

} // namespace toanl

#endif // __TOANL_SIGNAL_HPP__
