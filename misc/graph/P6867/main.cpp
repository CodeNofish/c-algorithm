#include <iostream>
#include <algorithm>

using namespace std;
#define N 504

int G[N][N];

int n;
long long m;

int visit[N][N];

// 换句话说，对于已知的现有状态，有唯一确定的下一状态。
// 如果将状态视为节点，批评的过程视为边的话，则每个节点出度均为1
void dfs(int x, int y, long long k) {
    if (visit[x][y])
        m = (m - k) % (k - visit[x][y]) + k;
    if (k == m) {
        cout << x;
        return;
    }
    visit[x][y] = k;
    // i-1  u->v
    // i    v->G[v][u]
    dfs(y, G[y][x], k + 1);
}

int
main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> G[i][j];
        }
    }
    dfs(1, 2, 1);   // 第1次 1批评2
    return 0;
}