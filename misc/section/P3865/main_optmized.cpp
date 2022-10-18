#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define N (100000+4)
int arr[N];

int st[N][21];
int lg[N];          // 缓存log

inline void init_st(int n) {
//    for (int i = 1; i <= n; i++)
//        st[i][0] = arr[i];
//    int k = (int) log2(n);
    int k = lg[n];
    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= n - (1 << j) + 1; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

inline int query(int l, int r) {
//    int k = (int) log2(r - l + 1);
    int k = lg[r - l + 1];
    // l..l+2^k-1
    // r-2^k+1...r-2^k+1 + 2^k-1 = r
    return max(st[l][k], st[r - (1 << (k)) + 1][k]);
}


int
main() {
    int n, m;
    int l, r;
    cin >> n >> m;

    lg[0] = -1;
    for (int i = 1; i <= n; i++) {
//        cin >> arr[i];
//        cin >> st[i][0];
        scanf("%d", &st[i][0]);
        lg[i] = lg[i >> 1] + 1;
    }
    init_st(n);
    for (int i = 0; i < m; i++) {
//        cin >> l >> r;
//        cout << query(l, r) << endl;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r));
    }
    return 0;
}