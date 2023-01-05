[![Build Status](https://travis-ci.org/niXman/static_if.svg?branch=master)](https://travis-ci.org/niXman/static_if)

static_if
=========

C++14 `static_if()` alternative implementation from D language

- // Emulation of "static if" feature from D language within function body, alpha version.
- // Original idea by Maxim Yanchenko (refer https://rsdn.ru/forum/cpp/5816278.flat.1)
- // Some improvements by Evgeny Panasyuk
- // Some improvements by niXman


Features:
=========
- allows to use it as expression: `auto r = STATIC_IF(...) { return 3; } STATIC_ELSE() { return 4; };`
- allows to have different result type of an expression: `auto r = STATIC_IF(...) { return 3; } STATIC_ELSE() { return 4.0; };`
- allows to have different branches depending on constexpr-condition: `auto r = STATIC_IF(is_same(T, std::string), v) { return v + "3"; } STATIC_ELSE(v) { return v + 4.0; };`
- allows to have constexpr result when C++17 is used
- zero run-time overhead

Overhead:
=========
For the following code sample:
```cpp
template<typename T>
__attribute__ ((noinline))
T foo(const T &v) {
    return STATIC_IF(is_same(T, int), v) {
        return v+3;
    } STATIC_ELSE(v) {
        return v+4;
    };
}

int main(int argc, char **argv) {
    int a = foo(argc);
    int b = *foo(argv[argc]);
    return a + b;
}
```
the following ASM will be generated:
```asm
char* foo<char*>(char* const&):
        lea     rax, [rdi+4]
        ret
int foo<int>(int const&):
        lea     eax, [rdi+3]
        ret
main:
        call    foo<int>(int const&)
        movsx   rdi, edi
        mov     rdi, QWORD PTR [rsi+rdi*8]
        mov     edx, eax
        call    foo<char*>(char* const&)
        movsx   eax, BYTE PTR [rax]
        add     eax, edx
        ret
```
As you can see, there is nothing superfluous here!
