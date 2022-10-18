#include <iostream>
#include <algorithm>
using namespace std;

#define N (100000+9)
#define M 23

int a[N * 3], b[N * 3];

int st[N * 3][M + 1];
int lg[N];

void init_st(int n) {
    for (int i = 1; i <= n; i++) {
        st[i][0] = a[i];
        st[i + n][0] = a[i];
        st[i + 2 * n][0] = a[i];
    }
    int k = lg[n];
    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= n - (1 << j) + 1; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            st[i + n][j] = max(st[i + n][j - 1], st[i + n + (1 << (j - 1))][j - 1]);
            st[i + 2 * n][j] = max(st[i + 2 * n][j - 1], st[i + 2 * n + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    int k = lg[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

void binary_search_result(int n) {
    int len = n / 2;
    // 处理中间链
    for (int i = n + 1; i <= n + n; i++) {
        int res = 0x7fffffff;

        if (query(i - len, i - 1) >= b[i]) {    // 存在答案
            int l = i - len, r = i - 1;         // 不取i
            while (l <= r) {
                int m = (l + r) >> 1;
                int a_max = query(m, i - 1);
                if (a_max >= b[i]) {            // find
                    res = min(res, i - m);      // i - m 弧长
                    l = m + 1;
                }
                else {
                    r = m - 1;
                }
            }
        }

        if (query(i + 1, i + len) >= b[i]) {
            int l = i + 1, r = i + len;
            while (l <= r) {
                int m = (l + r) >> 1;
                int a_max = query(i + 1, m);
                if (a_max >= b[i]) {
                    res = min(res, m - i);
                    r = m - 1;
                }
                else {
                    l = m + 1;
                }
            }
        }

        if (res == 0x7fffffff)
            cout << -1 << " ";
        else
            cout << res << " ";
    }
}

int
main() {
    int n, v;
    cin >> n;

    lg[0] = -1;
    for (int i = 1; i <= n; i++) {
        cin >> v;
        a[i] = a[i + n] = a[i + 2 * n] = v;
        lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i++) {
        cin >> v;
        b[i] = b[i + n] = b[i + 2 * n] = v;
    }
    init_st(n);
    binary_search_result(n);
}