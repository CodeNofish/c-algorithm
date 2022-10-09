#include <iostream>
#include <algorithm>

using namespace std;

#define INF 0x7fffffff
#define N 10
#define M 100

int vexnum = 10;
int edgenum = 100;
int G[N][N];

int dist[N];
int parent[N];
bool inS[N];    // 最短路径已经通过贪心 计算出来的节点集合

void dijkstra(int root) {
    for (int i = 0; i < vexnum; i++) {
        dist[i] = G[root][i];
        inS[i] = false;
        if (dist[i] == INF)
            parent[i] = -1;
        else
            parent[i] = root;
    }
    dist[root] = 0;
    inS[root] = true;
    for (int i = 0; i < vexnum; i++) {
        // find min dist in V-S
        int min = INF, next = root;
        for (int j = 0; j < vexnum; j++) {
            if (!inS[j] && dist[j] < min) {
                next = j;
                min = dist[j];
            }
        }
        // can't find min dist
        if (next == root) return;
        inS[next] = true;
        // update dist where maybe shorter through vex_next
        for (int j = 0; j < vexnum; j++) {
            if (!inS[j] && G[next][j] < INF) { // in V-S && edge exist
                if (dist[j] > dist[next] + G[next][j]) {
                    dist[j] = dist[next] + G[next][j];
                    parent[j] = next;
                }
            }
        }
    }
}

int
main() {

}