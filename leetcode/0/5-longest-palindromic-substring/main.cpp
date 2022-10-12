#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    // dp[i][j] = true  s[i..j]是回文串
    // dp[i][j] = true  when i==j
    // dp[i][j] = dp[i-1][j-1] & s[i]==s[j]
    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2) return s;

        int maxLen = 1, begin = 0;
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            dp[i][i] = true;
        for (int L = 2; L <= n; L++) {
            for (int i = 0; i < n; i++) {
                int j = i + L - 1;
                if (j >= n) break;

                if (s[i] != s[j]) {
                    dp[i][j] = false;
                }
                else {
                    if (j - i < 3)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (dp[i][j] && j - i + 1 > maxLen) {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxLen);
    }
};

int
main() {

}