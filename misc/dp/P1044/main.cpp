#include <iostream>
#include <algorithm>

using namespace std;

int f(int x) {
    if (x == 0)
        return 0;
    if (x == 1)
        return 1;
    // 放在前面和放在后面 2种情况
    return 2 * f(x - 1);
}

int
main() {
    int n;
    cin >> n;
    cout << f(n);
}