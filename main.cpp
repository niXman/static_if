
#include <static_if/static_if.hpp>

#include <iostream>
#include <type_traits>

using namespace std;

template<typename T>
auto test(const T &x) {
	int local;

	return STATIC_IF(is_same(T, std::string), x, local) {
		cout << "string: \"" << x << "\" of size=" << x.size() << "\t";
		int &z = local;
		(void)z;
		return "string branch"s;
	} STATIC_ELSE_IF(is_same(T, int), x) {
		cout << "integer: " << x << "\t";
		const int &z = x;
		(void)z;
		return "integer branch";
	} STATIC_ELSE(x, local) {
		cout << "else: " << x << "\t";
		int &z = local;
		(void)z;
		return 'E';
	};

	const auto v = STATIC_IF(is_same(T, std::integral_constant<int, 3>)) { return 3; } STATIC_ELSE() { return 4; };
	(void)v;
}

int main() {
	cout << test(1) << endl;
	cout << test(0.5) << endl;
	cout << test("Elbereth"s) << endl;
}
