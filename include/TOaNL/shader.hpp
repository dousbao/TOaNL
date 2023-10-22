#ifndef __TOANL_SHADER_HPP__
#define __TOANL_SHADER_HPP__

#include <vector>
#include <random>

namespace toanl {

struct shader {
public:
	shader(void) : _rd(), _gen(_rd()) {}

	std::vector<float> operator()(std::vector<std::pair<int, int>> cell)
	{
		std::geometric_distribution dict(0.1);
		std::vector<float> result(cell.size(), 0.2);

		for (std::size_t i = 0; i < result.size(); ++i)
			result[dict(_gen) % result.size()] += 0.2;

		return result;
	}

public:
	static char float2char(float degree)
	{
		if (degree <= 0.2)
			return '.';
		else if (degree <= 0.4)
			return ';';
		else if (degree <= 0.6)
			return '*';
		else if (degree <= 0.8)
			return '#';
		else
			return '@';
	}

private:
	std::random_device _rd;
	std::default_random_engine _gen;
};

} // namepsace toanl

#endif // __TOANL_SHADER_HPP__ 
