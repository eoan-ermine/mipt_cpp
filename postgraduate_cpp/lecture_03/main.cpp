template <typename T1, typename T2> struct A {
	void func(void) {}
};

int main() {
	A <int, double> a;
	A <float, double> b;

	a.func(); // for int
	b.func(); // for all
}