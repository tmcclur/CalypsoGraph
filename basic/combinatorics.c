#include "combinatorics.h"

size_t chooseTwo(int n) {
    size_t sum = 0;
    size_t l = (size_t)n;
    for (int i = 0; i < n; i++) {
        sum += --l;
    }
    return sum;
}
