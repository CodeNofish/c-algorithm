#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define N (300000 + 5)
bool ans[N];
int query[N];

vector<int> G[N];     // 压缩图集
set<int> cur_points;  // 当前点集

int pa[N];
int cnt[N];    // 所在联通分量的 点个数

void init_union_find(int n) {
    for (int i = 1; i <= n; ++i) {
        pa[i] = i;
        cnt[i] = 1;
    }
}

int find(int x) {
    return x == pa[x] ?
        x : pa[x] = find(pa[x]);
}

void merge(int x, int y) {
    int a = find(x), b = find(y);
    if (a == b) return;
    if (cnt[b] > cnt[a])
        swap(a,b);
    pa[a] = b;
    cnt[b] += cnt[a];
}

int
main()
{
    int n,m;
    int u,v;
    cin >> n >> m;
    // init union_find
    init_union_find(n);
    // create graph
    for (int i = 1; i <= m; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    // save query
    for (int i = 0; i < n; ++i)
        cin >> query[i];
    // 到放加点 倒着加边
    for (int i = n-1; i >= 0; --i) {
        int cur = query[i];             // 当前点
        cur_points.insert(cur);      // 把符合当前点集的边加入并查集，判断联通分量个数
        for (int & next : G[cur]) {
            if (cur_points.contains(next))
                merge(cur, next);
        }
        ans[i] = cnt[find(cur)] == cur_points.size();
    }
    // answer queries
    for (int i = 0; i < n; ++i)
        cout << (ans[i] ? "YES" : "NO") << endl;
}