#include <iostream>
#include <algorithm>

using namespace std;
#define MAX_M (100+4)
#define MAX_T (1000+4)

int et[MAX_M];
int em[MAX_M];
int dp[MAX_M][MAX_T];

int
main() {
    int t, m;
    cin >> t >> m;
    for (int i = 1; i <= m; i++) {
        cin >> et[i] >> em[i];
    }
    // dp[i][j]  i 选取前i-1的药草 j当前已经使用的时间
    // 时间不足时  dp[i-1][j]
    // 时间足够时  max(dp[i-1][j], dp[i-1][j+et[i]] + em[i])
    for (int i = 1; i <= m; i++) {          // 前i-1个
        for (int j = t; j >= 0; j--) {      // 当前剩余时间
            if (j < et[i])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - et[i]] + em[i]);
        }
    }
    cout << dp[m][t];
}