SPFA（Shortest Path Faster Algorithm）算法是Bellman-Ford算法的队列优化算法，
通常用于求解含负权边的单源最短路径，以及判负环。

最坏情况下，SPFA算法的时间复杂度和Bellman-Ford算法相同，为 O ( nm )；
但在稀疏图上运行效率较高，为 O ( km )，其中 k 是一个较小的常数。

```
（1）创建一个队列，首先源点 u 入队，标记 u 在队列中， u 的入队次数加1。

（2）松弛操作。取出队头节点 x ，标记 x 不在队列中。
    扫描 x 的所有出边 i ( x , v , w )，如果dis[ v ]>dis[ x ]+ e [ i ]. w ，则松弛，令dis[ v ]=dis[ x ]+ e [ i ]. w 。
    如果节点 v 不在队列中，判断 v 的入队次数加1后大于或等于 n ，则说明有负环，退出；
    否则 v 入队，标记 v 在队列中。
    
（3）重复松弛操作，直到队列为空。
```

SPFA算法有两个优化策略：SLF和LLL。

```
（1）SLF（Small Label First）策略：如果待入队的节点是 j ，队首元素为节点 i ，若dis[ j ]<dis[ i ]，则将 j 插入队首，否则插入队尾。

（2）LLL（Large Label Last）策略：设队首元素为节点 i ，队列中所有dis[]的平均值为 x ，若dis[ i ]> x ，则将节点 i 插入队尾，查找下一元素，直到找到某一节点 i 满足dis[ i ]≤ x ，将节点 i 出队，进行松弛操作。
```