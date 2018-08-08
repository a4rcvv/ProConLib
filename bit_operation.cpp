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

const unsigned int BIT_FLAG_0 = (1 << 0);
const unsigned int BIT_FLAG_1 = (1 << 1);
const unsigned int BIT_FLAG_2 = (1 << 2);
const unsigned int BIT_FLAG_3 = (1 << 3);
const unsigned int BIT_FLAG_4 = (1 << 4);
const unsigned int BIT_FLAG_5 = (1 << 5);
const unsigned int BIT_FLAG_6 = (1 << 6);
const unsigned int BIT_FLAG_7 = (1 << 7);

class Bit {
    unsigned int bit;

  public:
    // initializing
    Bit(const unsigned int &number) {
        bit = number;
    }
    Bit(const Bit &obj) {}
    void initialize(const unsigned int &number) {
        bit = number;
    }
    void operator=(const unsigned int &number) {
        bit = number;
    }
    // setting & erasing
    void set(const unsigned int &digit) {
        bit |= (1 << digit);
    }
    void set(const Bit &obj) {
        bit |= obj.bit;
    }
    void erase(const unsigned int &digit) {
        bit &= ~(1 << digit);
    }
    void erase(const Bit &obj) {
        bit &= ~obj.bit;
    }
    // getting bool_value
    bool is_on(const unsigned int &digit) {
        return bit & (1 << digit);
    }

    // getting bool_value (mask_bit)
    bool has_any(const Bit &obj) {
        return bit | obj.bit;
    }
    bool has_all(const Bit &obj) {
        return (bit & obj.bit) == bit;
    }
};
