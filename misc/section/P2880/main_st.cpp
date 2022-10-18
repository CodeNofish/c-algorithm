#include <iostream>
#include <algorithm>
using namespace std;

#define N (50000+4)
int h[N];

int min_st[N][33];
int max_st[N][33];
int lg[N];

void init_st(int n) {
    for (int i = 1; i <= n; i++) {
        min_st[i][0] = h[i];
        max_st[i][0] = h[i];
    }
    int k = lg[n];
    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= n - (1 << j) + 1; i++) {
            min_st[i][j] = min(min_st[i][j - 1], min_st[i + (1 << (j - 1))][j - 1]);
            max_st[i][j] = max(max_st[i][j - 1], max_st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    int k = lg[r - l + 1];
    int Max = max(max_st[l][k], max_st[r - (1 << k) + 1][k]);
    int Min = min(min_st[l][k], min_st[r - (1 << k) + 1][k]);
    return Max - Min;
}

int
main() {
    int n, q;
    int l, r;
    cin >> n >> q;

    lg[0] = -1;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        lg[i] = lg[i >> 1] + 1;
    }
    init_st(n);
    for (int i = 0; i < q; i++) {
        cin >> l >> r;
        cout << query(l, r) << endl;
    }
}