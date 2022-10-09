#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define N 5004
#define M 500004
#define MOD 80112002

int in_degree[N];
int out_degree[N];

struct Edge {
    int from,to,next;
};
Edge edges[M];
int head[N];        // 从该点出发的边 组成的链表 首个元素
int id = 0;
void add_edge(int from, int to) {
    id++;
    edges[id] = {from, to, head[from]};
    head[from] = id;
    in_degree[to]++;
    out_degree[from]++;
}

// dp[i] 到达i时的路径数
int dp[N];
queue<int> que;

// 拓扑,顺便dp路径个数
void topology(int n) {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            que.push(i);
            dp[i] = 1;
        }
    }
    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        //
        for (int i = head[cur]; i!=0; i = edges[i].next) {
            int next = edges[i].to;
            dp[next] = (dp[next] + dp[cur]) % MOD;
            if (--in_degree[next] == 0) {
                que.push(next);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (out_degree[i] == 0)
            res = (res + dp[i]) % MOD;
    }
    cout << res;
}

/*
 * DAG（有向无环图）不是求最短路
 *
 * 根据提示“最左端是不会捕食其他生物的生产者”可以想到，我们要入度为零的点开始查找；
 *
 * 再看一遍题目，就是求路径数，当且仅当一个点的入度变为零时才需要入队，并不是数据更新一次就要入队；
 *
 * 出度为零的点的路径总数和就是答案。
 */
int
main()
{
    int n,m,a,b;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> a >> b;
        add_edge(a, b);
    }
    topology(n);
}