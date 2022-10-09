#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define N 10
int n;
int G[N][N];

int in_degree[N];
int topo[N];

bool topo_sort() {
    int cnt = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0)
            q.push(i);
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        // add to res
        topo[cnt++] = cur;
        // remove cur_vex
        for (int next = 1; next <= n; next++) {
            if (G[cur][next] != 0) {    // has edge cur->next
                if (--in_degree[next] == 0)
                    q.push(next);
            }
        }
    }
    return cnt == n;
}

int
main() {

}