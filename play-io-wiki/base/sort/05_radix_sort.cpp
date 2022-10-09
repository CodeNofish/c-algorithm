#include <iostream>
#include <algorithm>
using namespace std;

/*
 * 是一种非比较型的排序算法，最早用于解决卡片排序的问题。
 *
 * 基数排序的工作原理是将待排序的元素拆分为  个关键字（比较两个元素时，
 * 先比较第一关键字，如果相同再比较第二关键字……）
 */