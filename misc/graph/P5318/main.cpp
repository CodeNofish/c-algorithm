#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define N (100000+4)
#define M (1000000+4)
int n, m;

vector<int> G[N];

bool seen[N];

void dfs0(int root) {
    seen[root] = true;
    cout << root << " ";

    for (int to: G[root]) {
        if (!seen[to])
            dfs0(to);
    }
}

void dfs() {
    for (int i = 1; i <= n; i++)
        seen[i] = false;
    dfs0(1);
    cout << endl;
}

void bfs() {
    for (int i = 1; i <= n; i++)
        seen[i] = false;
    queue<int> q;
    q.push(1);
    seen[1] = true;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << cur << " ";

        for (int to: G[cur]) {
            if (!seen[to]) {
                seen[to] = true;
                q.push(to);
            }
        }
    }
    cout << endl;
}

int
main() {
    int x, y;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        G[x].push_back(y);
    }
    for (int i = 1; i <= n; i++) {
        sort(G[i].begin(), G[i].end());
    }
    dfs();
    bfs();
}