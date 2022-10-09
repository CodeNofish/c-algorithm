如果遇到负权边，则在没有负环（回路的权值之和为负）存在时，
可以采用Bellman-Ford算法求解最短路径。

Bellman-Ford算法用于求解单源最短路径问题
该算法的优点是边的权值可以为负数、实现简单，缺点是时间复杂度过高。
但是，对该算法可以进行若干种优化，以提高效率。

Bellman-Ford算法与Dijkstra算法类似，都以松弛操作为基础。
Dijkstra算法以贪心法选取未被处理的具有最小权值的节点，然后对其出边进行松弛操作；
而Bellman-Ford算法对所有边都进行松弛操作，共 n -1次。
因为负环可以无限制地减少最短路径长度，所以如果发现第 n 次操作仍可松弛，则一定存在负环。

```
（1）数据结构。因为需要利用边进行松弛，因此采用边集数组存储。每条边都有三个域：两个端点 a 、 b 和边权 w 。

（2）松弛操作。对所有的边 j ( a , b , w )，如果dis[ e [ j ]. b ]>dis[ e [ j ]. a ]+ e [ j ]. w ，则松弛，令dis[ e [ j ]. b ]=dis[ e [ j ]. a ]+ e [ j ]. w 。其中，dis[ v ]表示从源点到节点 v 的最短路径长度。

（3）重复松弛操作 n -1次。

（4）负环判定（简称“判负环”）。再执行一次松弛操作，如果仍然可以松弛，则说明有负环。
```

松弛操作必定只会发生在最短路径松弛过的前驱节点上,
用一个队列记录松弛过的节点，可以避免冗余计算。