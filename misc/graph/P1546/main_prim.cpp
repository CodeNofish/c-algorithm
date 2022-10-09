#include <iostream>
#include <algorithm>

using namespace std;

#define N (100+4)
#define INF 0x7fffffff

int n;
int G[N][N];

int lowcost[N];
int closest[N];     // 记录父节点
bool inU[N];

void prim(int root) {
    // init
    for (int i = 1; i <= n; i++) {
        if (i == root) {
            lowcost[i] = 0;
            closest[i] = root;
            inU[i] = true;
            continue;
        }
        lowcost[i] = G[root][i];
        closest[i] = root;          // 总是可以相连
        inU[i] = false;
    }
    for (int i = 1; i <= n; i++) {
        // find min edge in V-U
        int min = INF, next = -1;
        for (int j = 1; j <= n; j++) {
            if (!inU[j] && min > lowcost[j]) {
                min = lowcost[j];
                next = j;
            }
        }
        if (next == -1) break;
        // add to U
        inU[next] = true;
        // update lowcost&closest by next
        for (int j = 1; j <= n; j++) {
            if (!inU[j] && G[next][j] < lowcost[j]) {
                lowcost[j] = G[next][j];
                closest[j] = next;
            }
        }
    }
}

// 你必须找出能连接所有农场并所用光纤最短的方案。
// 最小生成树 => Prim集合判边，Kruskal 排序边集+并查集
int
main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cin >> G[i][j];
    }
    prim(1);
    int res = 0;
    for (int i = 1; i <= n; i++)
        res += lowcost[i];
    cout << res;
}