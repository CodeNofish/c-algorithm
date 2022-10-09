Dijkstra算法用于求从源点到其他各个节点的最短路径。
Floyd算法可用于求解任意两个节点间的最短路径。

Floyd算法又被称为插点法，其算法核心是在节点 i 与节点 j 之间插入节点 k ，
看看是否可以缩短节点 i 与节点 j 之间的距离（松弛操作）。

```
（1）数据结构。设置地图的带权邻接矩阵为 G .Edge[][]，即如果从节点 i 到节点 j 有边，则 G .Edge[ i ][ j ]=< i , j >的权值，否则 G .Edge[ i ][ j ]=∞（无穷大）；采用两个辅助数组：最短距离数组dist[ i ][ j ]，记录从节点 i 到节点 j 的最短路径长度；前驱数组 p [ i ][ j ]，记录从节点 i 到节点 j 的最短路径上节点 j 的前驱。

（2）初始化。初始化dist[ i ][ j ]= G .Edge[ i ][ j ]，如果从节点 i 到节点 j 有边相连，则初始化 p [ i ][ j ]= i ，否则 p [ i ][ j ]=-1。

（3）插点。其实就是在节点 i 、 j 之间插入节点 k ，看是否可以缩短节点 i 、 j 之间的距离（松弛操作）。如果dist[ i ][ j ]>dist[ i ][ k ]+dist[ k ][ j ]，则dist[ i ][ j ]=dist[ i ][ k ]+dist[ k ][ j ]，记录节点 j 的前驱 p [ i ][ j ]= p [ k ][ j ]。
```

> https://zh.m.wikipedia.org/zh-hans/Floyd-Warshall%E7%AE%97%E6%B3%95