#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <charconv>
#include <chrono>
#include <cinttypes>
#include <ciso646>
#include <climits>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "config_macros.hpp"

#if !defined(__APPLE__)
#include <cuchar>
#endif

#include <cstdlib>
#include <cwchar>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <locale>
#include <map>
#include <numeric>
#include <ostream>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <version>

#if CONFIG_HAS_AT_LEAST_CXX_20
#include <concepts>
#include <numbers>
#include <ranges>
#endif

#if !CONFIG_HAS_AT_LEAST_CXX_17
#include <ccomplex>
#include <cstdalign>
#include <cstdbool>
#include <ctgmath>
#endif

#ifdef __linux__
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

#if !defined(__MINGW32__) && !defined(__MINGW64__) && defined(__has_include) && \
    __has_include(<gmp.h>) && __has_include(<gmpxx.h>) && __has_include(<mpfr.h>)

#include <gmp.h>
#include <gmpxx.h>
#include <mpfr.h>

#if defined(__clang__)
typedef __uint128_t uint128_t;
typedef __int128_t int128_t;
#elif defined(__GNUC__)
typedef __uint128_t uint128_t;
typedef __int128_t int128_t;
#elif defined(_MSC_VER)
#include <__msvc_int128.hpp>
typedef std::_Unsigned128 uint128_t;
typedef std::_Signed128 int128_t;
#else
#error "Unsupported compiler, typedef 128-bit integer specific for your compiler"
#endif

#endif

int main(int, const char* const[]) {
    std::at_quick_exit([]() noexcept { std::printf("at_quick_exit callback\n"); });
    std::atexit([]() noexcept { std::printf("atexit callback\n"); });

#ifdef __linux__
    on_exit(
        [](int status, void* arg) noexcept {
            std::printf("on_exit callback, status = %d, arg = %p\n", status, arg);
        },
        /*arg =*/reinterpret_cast<void*>(std::uintptr_t{0x12345678ABCDEFull}));
#endif

#ifdef __linux__
    const pid_t child_pid = fork();
    switch (child_pid) {
        case 0:
            printf("Hello from child %d\n", getpid());
            std::exit(0);
        case -1:
            std::terminate();
        default:
            if (waitpid(child_pid, nullptr, 0) == -1) {
                std::perror("waitpid");
                std::terminate();
            }
    }
#endif

    assert(true);
    static_assert(true);

    std::puts("Hell");
    std::cout << "Hell" << std::endl;

    std::thread([]() {
        std::cout << "Hello from the thread " << std::this_thread::get_id() << '\n';
    }).join();

#if CONFIG_HAS_AT_LEAST_CXX_20
    std::jthread([]() {
        std::cout << "Hello from the jthread " << std::this_thread::get_id() << '\n';
    }).join();
#endif

    using namespace std::literals;
#if CONFIG_HAS_AT_LEAST_CXX_20 && defined(__GNUG__) && !defined(__clang__)
    constexpr auto c = 1.0 + 1.0i;
    static_assert(c.imag() == 1.0);
#else
    constexpr std::complex c{1.0, 1.0};
    static_assert(c.imag() == 1.0, "");
#endif

    constexpr auto sv = "abc"sv;
    static_assert(sv.size() == 3, "");

    static const auto s = "abc"s;
    assert(s.size() == 3);

    constexpr auto time = 100ms;
    static_assert(std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() ==
                      time.count() * 1'000'000,
                  "");

#if CONFIG_HAS_AT_LEAST_CXX_20
    static constinit const std::bitset<64> set(uint64_t(-1));
    static constinit thread_local const int some1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    static constexpr int some2[]                    = {1, 2, 3, 4, 5, 6, 7, 8};
    assert(std::ranges::equal(some1, some2));
#else
    static const std::bitset<64> set(uint64_t(-1));
#endif
    assert(set.all());
}
