
#include <static_if/static_if.hpp>

#include <boost/preprocessor/stringize.hpp>

#include <iostream>
#include <stdexcept>

using namespace std::string_literals;

/***************************************************************************/

#define RUN_TEST(testname) \
	std::cout << "exec test \"" << #testname << "\"..."; \
	testname(); \
	std::cout << "done" << std::endl

#define CHECK_RESULT_TYPE(testname, var, ...) \
	static_assert( \
		 std::is_same<decltype(var), __VA_ARGS__>::value \
		,#testname "(" BOOST_PP_STRINGIZE(__LINE__) "): \"" #var "\" should be of a type \"" #__VA_ARGS__ "\"" \
	)

#define CHECK_RESULT_VAL(testname, var, ...) \
	if ( var != __VA_ARGS__ ) { \
		throw std::runtime_error(#testname "(" BOOST_PP_STRINGIZE(__LINE__) "): bad \"" #var "\" value"); \
	}

/***************************************************************************/

template<typename T>
auto test00(const T &x) {
	int local;

	return STATIC_IF(is_same(T, std::string), x, local) {
		int &z = local;
		(void)z;
		return 3;
	} STATIC_ELSE_IF(is_same(T, int), x) {
		const int &z = x;
		(void)z;
		return 3L;
	} STATIC_ELSE(x, local) {
		int &z = local;
		(void)z;
		return '3';
	};
}

void test00() {
	auto r00 = test00(1);
	CHECK_RESULT_TYPE(test00, r00, long);

	auto r01 = test00(.5);
	CHECK_RESULT_TYPE(test00, r01, char);

	auto r02 = test00("Elbereth"s);
	CHECK_RESULT_TYPE(test00, r02, int);
}

/***************************************************************************/

constexpr bool some_constexpr_function() { return true; }
constexpr bool some_constexpr_var = false;

void test01() {
	auto r00 = STATIC_IF(userpred(some_constexpr_function())) { return 3; } STATIC_ELSE() { return '3'; };
	CHECK_RESULT_TYPE(test01, r00, int);

	auto r01 = STATIC_IF(userpred(some_constexpr_var)) { return '3'; } STATIC_ELSE() { return 3; };
	CHECK_RESULT_TYPE(test01, r01, int);

	auto r02 = STATIC_IF(userpred(!some_constexpr_function())) { return 3; } STATIC_ELSE() { return '3'; };
	CHECK_RESULT_TYPE(test01, r02, char);

	auto r03 = STATIC_IF(userpred(!some_constexpr_var)) { return '3'; } STATIC_ELSE() { return 3; };
	CHECK_RESULT_TYPE(test01, r03, char);

	auto r04 = STATIC_IF(not_userpred(some_constexpr_function())) { return 3; } STATIC_ELSE() { return '3'; };
	CHECK_RESULT_TYPE(test01, r04, char);

	auto r05 = STATIC_IF(not_userpred(some_constexpr_var)) { return '3'; } STATIC_ELSE() { return 3; };
	CHECK_RESULT_TYPE(test01, r05, char);
}

/***************************************************************************/

template<typename T>
auto add(const T &l, const T &r) {
	return STATIC_IF(is_same(T, std::string), l, r) {
		const auto lv = std::stoi(l);
		const auto rv = std::stoi(r);
		return std::to_string(lv+rv);
	} STATIC_ELSE_IF(is_same(T, int), l, r) {
		return l+r;
	} STATIC_ELSE() {
		throw std::invalid_argument("T is neither \"std::string\" nor \"int\"");
	};
}

void test02() {
	auto r00 = add("2"s, "2"s);
	CHECK_RESULT_TYPE(test02, r00, std::string);
	CHECK_RESULT_VAL(test02, r00, "4"s);
}

/***************************************************************************/

int main() {
	RUN_TEST(test00);
	RUN_TEST(test01);
	RUN_TEST(test02);
}

/***************************************************************************/
