#include <algorithm>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

uint64_t get_combination_count(uint_fast16_t, uint_fast16_t);
uint64_t get_permutation_count(uint_fast16_t, uint_fast16_t);
uint64_t get_factorial(uint_fast16_t);

uint64_t get_combination_count(uint_fast16_t n, uint_fast16_t r) {
    if (n < r) {
        // error
        return 0;
    }
    uint_fast16_t d = n - r;
    uint64_t result = 1;
    while (n > 1 || d > 1 || r > 1) {
        if (n > 1) {
            result *= n;
            n--;
        }
        if (d > 1 && result % d == 0) {
            result /= d;
            d--;
        }
        if (r > 1 && result % r == 0) {
            result /= r;
            r--;
        }
    }
    return result;
}

uint64_t get_permutation_count(uint_fast16_t n, uint_fast16_t r) {
    if (n < r) {
        // error
        return 0;
    }
    uint64_t result = 1;
    for (uint_fast16_t i = n; i > n - r; i--) {
        result *= i;
    }
    return result;
}

uint64_t get_factorial(uint_fast16_t n) {
    uint64_t result = 1;
    for (uint_fast16_t i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}
