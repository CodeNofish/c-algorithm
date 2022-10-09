#include <iostream>
#include <algorithm>

using namespace std;

#define N 10
#define M 100
#define INF 0x7fffffff
int vexnum = 10;
int edgenum = 100;
int G[N][N];

int closest[N]; // 上一个邻近的节点
int lowcost[N]; // 顶点i 加入集合的最小代价
bool inU[N];    // 已经加入集合

void prim(int root) {
    // init
    inU[root] = true;
    for (int i = 1; i <= vexnum; i++) {
        if (i != root) {
            lowcost[i] = G[root][i];
            closest[i] = root;
            inU[i] = false;
        }
        else {
            lowcost[i] = 0;
        }
    }
    // 在V-U集合中找 距离集合U最近的节点t
    for (int i = 1; i < vexnum; i++) {
        int min = INF, t = -1;
        for (int j = 1; j <= vexnum; j++) {
            if (!inU[j] && lowcost[j] < min) {
                t = j;
                min = lowcost[j];
            }
        }
        // 找不到
        if (t == -1) break;
        // add t to U
        inU[t] = true;
        // update lowcost&closest by t
        for (int j = 1; j <= vexnum; j++) {
            if (!inU[j] && lowcost[j] > G[t][j]) {
                lowcost[j] = G[t][j];
                closest[j] = t;
            }
        }
    }
}

int
main() {

}