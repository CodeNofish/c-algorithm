#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define N 1000
int in_degree[N];
int out_degree[N];
bool seen[N];
vector<int> G[N];
queue<int> que;

// tarjan缩点 可以转换为有向吴环图
// 有向无环图DAG 才能拓扑排序, 入度为0才加入队列, 不断删去点该出去的边
int level;
void topology(int n) {
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0)
            que.push(i);
    }
    while (!que.empty()) {
        unsigned long size = que.size();  // 当前层大小
        while (size-- > 0) {
            int cur = que.front();
            que.pop();
            seen[cur] = true;
            // do something for vertex
            for (auto next : G[cur]) {
                if (seen[next]) continue;
                if (--in_degree[next] == 0)
                    que.push(next);
            }
        }
        // do something for level
        level++;
    }
    cout << level;
}

int
main()
{
    int n,m;
    int a, b;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        G[b].push_back(a);
        in_degree[a]++;
        out_degree[b]++;
    }
    topology(n);
}