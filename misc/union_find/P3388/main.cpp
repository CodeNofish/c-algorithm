#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

// 节点的个数
#define N 20004
vector<int> G[N];   // adj

int dfn[N];         // dfn[x] 代表节点 x 对应的时间戳
int low[N];         // 该顶点 不通过父顶点 能访问到的祖先顶点中最小时间戳
int parent[N];      // 用于更新low值的时候排除父顶点
bool seen[N];
bool cut_points[N];

int cnt = 0;         // 计数


// root
void tarjan(int cur, int root) {
    int children_tree = 0;      // 根节点子树个数(单独处理根节点)
    dfn[cur] = low[cur] = ++cnt;
    seen[cur] = true;

    for (auto next : G[cur]) {
        if (!seen[next]) {
            // cur-next 是树边
            if (cur == root)    children_tree++;    // (单独处理根节点)

            parent[next] = cur;
            tarjan(next, root);       // 计算子树low dfn
            // 定义传递性
            // 该顶点 不通过父顶点 能访问到的祖先顶点中最小时间戳
            low[cur] = min(low[cur], low[next]);

            if (cur != root && low[next] >= dfn[cur]) {
                // 不是根节点,且next不通过父节点cur 能访问到的最小时间戳 大于等于当前序列
                // (必须通过cur才能访问更多)
                cut_points[cur] = true;
            }
        } else if (parent[cur] != next) {
            // cur-next 是回边 且不是回父亲(需要更新low)
            low[cur] = min(low[cur], dfn[next]);
        }
    }
    if (cur == root && children_tree >= 2) {
        // 是根节点,且根节点有两个以上子树,是割点
        cut_points[cur] = true;
    }
}


int n, m;
int main() {
    int x, y;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);
    }

    // seen 数组可以省略,用dfn=0的情况替代
    memset(seen, false, n);
    memset(parent, -1, n);
    memset(dfn, 0, n);
    memset(cut_points, false, n);

    for (int i = 0; i < n; ++i) {
        if (!seen[i]) {
            tarjan(i, i);
        }
    }
    // output
    int cut_points_cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (cut_points[i])
            cut_points_cnt++;
    }
    cout << cut_points_cnt << endl;
    for (int i = 0; i < n; ++i) {
        if (cut_points[i])
            cout << (i+1) << " ";
    }
}