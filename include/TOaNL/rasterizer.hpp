#ifndef __TOANL_RASTERIZER_HPP__
#define __TOANL_RASTERIZER_HPP__

#include <vector>
#include <stdexcept>
#include <algorithm>

namespace toanl {

struct rasterizer {
public:
	std::vector<std::pair<int, int>> operator()(const std::vector<std::pair<int, int>> &vertex)
	{
		if (vertex.size() < 3)
			throw std::runtime_error("can't form polygon with less than 3 vertices");

		std::vector<std::pair<int, int>> cell;
		std::vector<std::pair<int, int>> sorted_vertex(vertex);
		
		std::sort(sorted_vertex.begin(), sorted_vertex.end(), [](const auto &a, const auto &b){
			return a.second < b.second;
		});

		int min_y = sorted_vertex.front().second;
		int max_y = sorted_vertex.back().second;

		for (int y = min_y; y <= max_y; ++y) {
			std::vector<int> intersec;

			for (std::size_t i = 0; i < vertex.size(); ++i) {
				std::pair<int, int> p1 = vertex[i];
				std::pair<int, int> p2 = vertex[(i + 1) % vertex.size()];

				if (p1.second == p2.second)
					continue;

				if (std::min(p1.second, p2.second) <= y && y < std::max(p1.second, p2.second))
					intersec.push_back(p1.first + (p2.first - p1.first) * (y - p1.second) / (p2.second - p1.second));
			}

			std::sort(intersec.begin(), intersec.end());

			for (std::size_t i = 0; i < intersec.size(); i += 2) {
				int start = intersec[i], end = intersec[i + 1];

				for (int x = start; x <= end; ++x)
					cell.push_back(std::make_pair(x, y));
			}
		}

		return cell;
	}
};

} // namepsace toanl

#endif // __TOANL_RASTERIZER_HPP__
