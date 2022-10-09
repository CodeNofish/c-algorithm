#include <iostream>
#include <algorithm>

using namespace std;

#define SWAP(x, y)     \
if (x != y) {          \
    x ^= y;            \
    y ^= x;            \
    x ^= y;            \
}

int
main() {
    int x = 1, y = 2;
    SWAP(x, y);
    cout << x << " " << y;
}