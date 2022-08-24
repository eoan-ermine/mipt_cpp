#include <iostream>
#include <concepts>

template <typename T1, typename T2> struct A {
	void func(void) {
		if constexpr (std::is_same_v<T1, int>) {
			std::cout << "for int\n";
		} else {
			std::cout << "for all\n";
		}
	}
};

int main() {
	A <int, double> a;
	A <float, double> b;

	a.func(); // for int
	b.func(); // for all
}
