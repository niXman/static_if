
#include <static_if/static_if.hpp>

#include <iostream>
#include <stdexcept>

#define _STRINGIZE(x) #x
#define STRINGIZE(x) _STRINGIZE(x)

/***************************************************************************/

#define RUN_TEST(testname) \
    std::cout << "exec test \"" << #testname << "\"..."; \
    testname(); \
    std::cout << "done" << std::endl

#define CHECK_RESULT_TYPE(testname, var, ...) \
    static_assert( \
         std::is_same<decltype(var), __VA_ARGS__>::value \
        ,#testname "(" STRINGIZE(__LINE__) "): \"" #var "\" should be of a type \"" #__VA_ARGS__ "\"" \
    )

#define CHECK_RESULT_VAL(testname, var, ...) \
    if ( var != __VA_ARGS__ ) { \
        throw std::runtime_error(#testname "(" STRINGIZE(__LINE__) "): bad \"" #var "\" value"); \
    }

/***************************************************************************/

template<typename T>
auto test00(const T &x) {
    int local;

    return STATIC_IF(is_same(T, std::string), x, local) {
        const std::string &y = x;
        (void)y;
        int &z = local;
        (void)z;
        return 3;
    } STATIC_ELSE_IF(is_same(T, int), x) {
        const int &z = x;
        (void)z;
        return 4L;
    } STATIC_ELSE(x, local) {
        (void)x;
        int &z = local;
        (void)z;
        return '5';
    };
}

void test00() {
    auto r00 = test00(1);
    CHECK_RESULT_TYPE(test00, r00, long);
    CHECK_RESULT_VAL (test00, r00, 4);

    auto r01 = test00(.5);
    CHECK_RESULT_TYPE(test00, r01, char);
    CHECK_RESULT_VAL (test00, r01, '5');

    auto r02 = test00(std::string{"Elbereth"});
    CHECK_RESULT_TYPE(test00, r02, int);
    CHECK_RESULT_VAL (test00, r02, 3);
}

/***************************************************************************/

constexpr bool some_constexpr_function() { return true; }
constexpr bool some_constexpr_var = false;

void test01() {
    auto r00 = STATIC_IF(userpred(some_constexpr_function())) { return 3; } STATIC_ELSE() { return '4'; };
    CHECK_RESULT_TYPE(test01, r00, int);
    CHECK_RESULT_VAL(test01, r00, 3);

    auto r01 = STATIC_IF(userpred(some_constexpr_var)) { return '4'; } STATIC_ELSE() { return 3; };
    CHECK_RESULT_TYPE(test01, r01, int);
    CHECK_RESULT_VAL(test01, r01, 3);

    auto r02 = STATIC_IF(userpred(!some_constexpr_function())) { return 3; } STATIC_ELSE() { return '4'; };
    CHECK_RESULT_TYPE(test01, r02, char);
    CHECK_RESULT_VAL(test01, r02, '4');

    auto r03 = STATIC_IF(userpred(!some_constexpr_var)) { return '4'; } STATIC_ELSE() { return 3; };
    CHECK_RESULT_TYPE(test01, r03, char);
    CHECK_RESULT_VAL(test01, r03, '4');

    auto r04 = STATIC_IF(not_userpred(some_constexpr_function())) { return 3; } STATIC_ELSE() { return '4'; };
    CHECK_RESULT_TYPE(test01, r04, char);
    CHECK_RESULT_VAL(test01, r04, '4');

    auto r05 = STATIC_IF(not_userpred(some_constexpr_var)) { return '4'; } STATIC_ELSE() { return 3; };
    CHECK_RESULT_TYPE(test01, r05, char);
    CHECK_RESULT_VAL(test01, r05, '4');
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
        throw std::invalid_argument("\"T\" is neither \"std::string\" nor \"int\"");
        return .0;
    };
}

void test02() {
    auto r00 = add(std::string{"2"}, std::string{"2"});
    CHECK_RESULT_TYPE(test02, r00, std::string);
    CHECK_RESULT_VAL(test02, r00, std::string{"4"});

    auto r01 = add(2, 2);
    CHECK_RESULT_TYPE(test02, r01, int);
    CHECK_RESULT_VAL(test02, r01, 4);

    bool ok = false;
    try {
        auto r02 = add(.2, .2);
        CHECK_RESULT_TYPE(test02, r02, double);
        CHECK_RESULT_VAL(test02, r02, 0.04);
    } catch (...) {
        ok = true;
    }
    CHECK_RESULT_VAL(test02, ok, true);
}

/***************************************************************************/

void test03() {
    auto r00 = STATIC_IF(is_any_of(int, char, float, unsigned)) {
        return 0;
    } STATIC_ELSE() {
        return 1;
    };
    CHECK_RESULT_VAL(test03, r00, 1);

    auto r01 = STATIC_IF(is_any_of(int, char, int, unsigned)) {
        return 0;
    } STATIC_ELSE() {
        return 1;
    };
    CHECK_RESULT_VAL(test03, r01, 0);

    auto r02 = STATIC_IF(is_not_any_of(int, char, float, unsigned)) {
        return 0;
    } STATIC_ELSE() {
        return 1;
    };
    CHECK_RESULT_VAL(test03, r02, 0);

    auto r03 = STATIC_IF(is_not_any_of(int, char, int, unsigned)) {
        return 0;
    } STATIC_ELSE() {
        return 1;
    };
    CHECK_RESULT_VAL(test03, r03, 1);
}

/***************************************************************************/

int main() {
    RUN_TEST(test00);
    RUN_TEST(test01);
    RUN_TEST(test02);
    RUN_TEST(test03);
}

/***************************************************************************/
