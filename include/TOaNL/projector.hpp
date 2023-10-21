#ifndef __TOANL_PROJECTOR_HPP__
#define __TOANL_PROJECTOR_HPP__

#include <tuple>

namespace toanl {

struct projector {
	std::pair<int, int> operator()(std::tuple<int, int, int> point_3d)
	{
		return std::make_pair(std::get<0>(point_3d), std::get<1>(point_3d));
		// auto [x, y, z] = point_3d;
		// return std::make_pair(x / z, y / z);
	}
};

} // namespace toanl

#endif // __TOANL_PROJECTOR_HPP__
