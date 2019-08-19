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

int get_gcd(int a, int b) {
    if (a < b)
        std::swap(a, b);
    int r;
    while (1) {
        r = a % b;
        if (r == 0) {
            return b;
        } else {
            a = b;
            b = r;
        }
    }
}