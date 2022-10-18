#include <iostream>
#include <algorithm>
using namespace std;

#define N (1000000+4)

int arr[N];
int st[N][33];
int lg[N];

void init_st(int n) {
    for (int i = 1; i <= n; i++)
        st[i][0] = arr[i];
    int k = lg[n];
    for (int j = 1; j <= k; j++)
        for (int i = 1; i <= n - (1 << j) + 1; i++)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

inline int query(int l, int r) {
    int k = lg[r - l + 1];
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}

int
main() {
    int n, m;
    cin >> n >> m;

    lg[0] = -1;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        lg[i] = lg[i >> 1] + 1;
    }
    init_st(n);
    for (int i = 1; i + m - 1 <= n; i++)
        cout << query(i, i + m - 1) << endl;
}