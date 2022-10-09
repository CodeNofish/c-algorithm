#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define N (1000000+4)

char a[N],b[N];
size_t len_a, len_b;

// 从pos开始找
int bf(int pos) {
    int i = pos, j = 0;
    while (i < len_a && j < len_b) {
        if (a[i] == b[i]) {
            i++;
            j++;
        }
        else {
            i = i - j + 1;  // 回退
            j = 0;
        }
    }
    return j >= len_b ? i - (int)len_b + 1 : 0;
}

int
main()
{
    cin >> a >> b;
    len_a = strlen(a);
    len_b = strlen(b);

    cout << bf(0);
}