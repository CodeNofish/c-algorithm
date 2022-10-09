#include <iostream>
#include <algorithm>

using namespace std;
#define MAX_N (1000+4)
#define MAX_V (1000+4)

int dp[MAX_N][MAX_V];   // dp[i][j] 前i个骨头 放到容量位j的背包 最大价值
int val[MAX_N];         // 第i个骨头的价值
int volume[MAX_N];           // v[i] 体积

int
main() {
    int t;
    int n, v;
    cin >> t;
    while (t--) {
        cin >> n >> v;
        for (int i = 1; i <= n; i++)
            cin >> val[i];
        for (int i = 1; i <= n; i++)
            cin >> volume[i];

        for (int i = 0; i <= n; i++)
            dp[i][0] = 0;
        for (int i = 0; i <= n; i++)
            dp[0][i] = 0;

        for (int i = 1; i <= n; i++) {      // 前i个骨头
            for (int j = 1; j <= n; j++) {  // 背包大小
                if (j < volume[i])   // 放不下
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - volume[i]] + val[i]);
            }
        }
        cout << dp[n][v] << endl;
    }
}