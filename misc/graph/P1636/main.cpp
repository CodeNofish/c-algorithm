#include <iostream>
#include <algorithm>

using namespace std;

#define N (1000+4)

int n, m;
int degree[N];

int
main() {
    int a, b;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        degree[a]++;
        degree[b]++;
    }
    // 奇点（顶点度数为奇数）
    int odd_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 != 0)
            odd_cnt++;
    }
    if (odd_cnt != 0)
        // 连通图只可能有偶数个奇点
        // 若每多出两个奇点，那么画的次数就会+1
        cout << (odd_cnt / 2);
    else
        // 咦，发现这3个点都不是奇数点，但也可以一笔画完
        cout << (odd_cnt + 1);
}