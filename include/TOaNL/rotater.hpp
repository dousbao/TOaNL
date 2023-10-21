#ifndef __TOANL_ROTATER_HPP__
#define __TOANL_ROTATER_HPP__

#include <tuple>
#include <vector>
#include <cmath>

namespace toanl {

class rotater {
public:
	explicit rotater(const std::vector<std::tuple<int, int, int>> &points) : center(0)
	{
		for (int i = 0; i < points.size(); ++i)
			center += std::get<0>(points[i]);
		center /= points.size();
	}

public:
	std::tuple<int, int, int> operator()(const std::tuple<int, int, int> &point, double radians)
	{
		double x = std::get<0>(point) - center;
		double y = std::get<1>(point);
		double z = std::get<2>(point);

		double cos = std::cos(radians), sin = std::sin(radians);
		int new_x = std::round(x * cos + z * sin);
		int new_y = y;
		int new_z = std::round(-x * sin + z * cos);

		new_x += center;

		return std::make_tuple(new_x, new_y, new_z);
	}

private:
	int center;
};

} // namespace rotate

#endif // __TOANL_ROTATER_HPP__
