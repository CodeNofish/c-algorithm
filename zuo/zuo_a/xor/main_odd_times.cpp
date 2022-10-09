#include <iostream>
#include <algorithm>

using namespace std;

int
main() {
    // 出现 1奇数次，其他出现偶数次
    int arr[] = {1, 2, 2, 3, 3, 3, 3};

    int odd_num = 0;
    for (int i: arr)
        odd_num ^= i;

    cout << odd_num;
}