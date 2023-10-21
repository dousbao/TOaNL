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
		std::exponential_distribution<> dist(1);
		std::vector<float> result(cell.size(), 0);

		for (std::size_t i = 0; i < result.size(); ++i) {
			int random = dist(_gen);
			result[result.size() - random] = random; 
		}

		return result;
	}

private:
	std::random_device _rd;
	std::default_random_engine _gen;
};

} // namepsace toanl

#endif // __TOANL_SHADER_HPP__ 
