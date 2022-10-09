给定 n 种物品，每种物品都有重量 w i 和价值 v i ，每种物品的数量都可以大于1但是有限制。
第 i 种物品有 c i 个。背包容量为 W ，求解在不超过背包容量的情况下如何放置物品，可以使背包中物品的价值之和最大。
我们可以将多重背包问题通过暴力拆分或二进制拆分转化为01背包问题，也可以通过数组优化对物品数量进行限制。

* 暴力拆分

```c++
for (i=1; i<=n; i++)
    for (k=1; k<=c[i]; k++)     // added
        for (j=W; j>=w[i]; j--)
            dp[j] = max(dp[j], dp[j-w[i]] + v[i]);
```

* 二进制拆分

```c++
for (i=1; i<=n; i++) {
    if (c[i]*w[i] >= W) {   // 完全够用 转为完全背包
        for (j=w[i]; j<=maxn; j++)
            dp[j] = min(dp[j], dp[j-w[i]] + v[i]);
    }
    else {
        for (k=1; c[i]>0; k<<=1) {
            int x = min(k, c[i]);
            for (j=W; j>=w[i]*x; j--)   // 01
                dp[j] = min(dp[j], dp[j-w[i]*x] + v[i]*x);
            c[i] -= x;
        }
    }
}
```

* 数组优化

```c++
for (i=1; i<=n; i++)
    memset(num, 0, sizeof(num));    // 记录容量为j时 放入多少个第i种物品
    for (j=w[i]; j<=W; j++) {
        if (dp[j] < dp[j-w[i]] + v[i] && num[j-w[i]] < c[i]) {
            dp[j] = dp[j-w[i]] + v[i];
            num[j] = num[j-w[i]] + 1;
        }
    }
```