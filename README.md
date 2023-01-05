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
T foo(const T &v) {
    return STATIC_IF(is_same(T, int), v) {
        return v+3;
    } STATIC_ELSE(v) {
        return v+4;
    };
}

int main(int argc, char **argv) {
    if ( argc == 1 ) {
        return foo(argc);
    }

    if ( argc == 2 ) {
        const char *v = foo(argv[argc]);
        return *v;
    }
}
```
the following ASM will be generated:
```asm
main:
        mov     eax, 4
        cmp     edi, 1
        je      .L4
        xor     eax, eax
        cmp     edi, 2
        je      .L9
.L4:
        ret
.L9:
        mov     rax, QWORD PTR [rsi+16]
        movsx   eax, BYTE PTR [rax+4]
        ret
```
