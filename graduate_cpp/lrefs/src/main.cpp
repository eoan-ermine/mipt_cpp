#include "../include/triangle.hpp"

#include <unordered_set>
#include <iostream>
#include <vector>

int main() {
	int N; std::cin >> N;
	
	std::vector<Triangle3D> triangles(N);
	for (auto& triangle: triangles) {
		std::cin >> triangle;
	}

	std::unordered_set<int> intersections;
	for (std::size_t lIdx = 0, size = triangles.size(); lIdx != size; ++lIdx) {
		const auto& lhs = triangles[lIdx];
		for (auto rIdx = lIdx + 1; rIdx != size; ++rIdx) {
			const auto& rhs = triangles[rIdx];
			if (lhs.intersects(rhs)) {
				intersections.insert(lIdx);
				intersections.insert(rIdx);
			}
		}
	}

	std::copy(intersections.begin(), intersections.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << '\n';
}