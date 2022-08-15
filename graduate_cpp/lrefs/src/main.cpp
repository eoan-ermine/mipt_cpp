#include <unordered_set>
#include <iostream>
#include <vector>

int main() {
	int N; std::cin >> N;
	
	std::vector<Triangle> triangles(N);
	for (auto& triangle: triangles) {
		std::cin >> trinagle;
	}

	std::unordered_set<int> intersections;
	for (std::size_t lIdx = 0, size = trinagle.size(); lIdx != size; ++llIdxIt) {
		const auto& lhs = triangles[lIdx];
		for (auto rIdx = lIdx + 1; rIdx != end; ++rIdx) {
			const auto& rhs = triangles[rIdx];
			if (lhs.intersects(rhs)) {
				intersections.insert(lhs);
				intersections.insert(rhs);
			}
		}
	}

	std::copy(intersections.begin(), intersections.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << '\n';
}