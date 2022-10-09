## 差分约束

差分约束系统 是一种特殊的 n元一次不等式组，
它包含 n个变量 以及 m个约束条件，
每个约束条件是由两个其中的变量做差构成的

x_i - y_j <= c_k,

xa-xb >= c

---

求最短路径 缩小条件 `dist[v] > dist[u] + w[u,v]`,
是为了满足 `dist[v] <= min { dist[u] + w[u,v] }`.

求解 `xi - xj <= c` => `xi <= c + xj`,
需要满足 `xi <= min { xj + c }`,
超级源点,约束x, `dist[i] <= min { dist[j] + c}`,
更新条件为, `dist[i] > dist[j] + c`,
转换为符合最短路径的边, `dist[i] > dist[j] + w[j,i]`,
所以对于边组, `<j,i,c>`.

---