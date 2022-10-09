#include <algorithm>
#include <iostream>

using namespace std;

// 货物重量
static int w[] = {4,10,7,11,3,5,14,2};
// 载重
static int c = 30;

int
main()
{
    double tmp = 0.0;   // 已经装载的载重
    int ans = 0;        // 装载个数
    int n = sizeof(w) / sizeof(int);

    // 贪心策略 先装代价小的
    sort(w, w+n);
    for (int i = 0; i < n; ++i) {
        tmp += w[i];
        if (tmp <= c)
            ans++;
        else
            break;
    }
    cout << ans << endl;
}