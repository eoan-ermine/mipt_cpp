#include <iostream>

template <typename T1, typename T2> struct A {
	void func(void) {
		std::cout << "for all\n";
	}
};

template <typename T2> struct A <int, T2> {
	void func(void) {
		std::cout << "for int\n";
	}
};

int main() {
	A <int, double> a;
	A <float, double> b;

	a.func(); // for int
	b.func(); // for all
}
