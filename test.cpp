#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <ostream>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

#if __cplusplus >= 202002L
#include <concepts>
#include <numbers>
#include <ranges>
#endif

#include "config_macros.hpp"

#if !defined(__MINGW32__) && !defined(__MINGW64__)

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

int main() {
    assert(true);
    static_assert(true);
    puts("Hell");
    std::cout << "Hell" << std::endl;
    std::thread t([]() noexcept { puts("Hello from some thread"); });
    t.join();
}
