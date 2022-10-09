#include <iostream>
#include <algorithm>

using namespace std;

#define MAXBIT    100
#define MAXLEAF   30
#define MAXNODE   (MAXLEAF*2-1)

// 结点结构体
struct HNode {
    double weight;
    int parent;
    int lchild;
    int rchild;
    char value;
};
// 编码结构体
struct HCode {
    int bit[MAXBIT];    // 存储编码的数组
    int start;          // 编码开始下标
};

HNode huffman_nodes[MAXNODE];
HCode huffman_codes[MAXLEAF];

void build_huffman_tree(int n) {
    int x1, x2;
    double m1, m2;
    // 初始化存放哈夫曼树数组 HuffNode[] 中的结点
    for (int i = 0; i < 2 * n - 1; i++) {
        huffman_nodes[i].weight = 0;
        huffman_nodes[i].parent = -1;
        huffman_nodes[i].lchild = -1;
        huffman_nodes[i].rchild = -1;
    }
    // 输入 n 个叶子结点的权值
    for (int i = 0; i < n; i++) {
        cout << "Please input value and weight of leaf node " << i + 1 << endl;
        cin >> huffman_nodes[i].value >> huffman_nodes[i].weight;
    }
    // 构造 Huffman 树

}

int
main() {
    int i, j, n;
    cout << "Please input n:" << endl;
    cin >> n;
    build_huffman_tree(n);  //构造哈夫曼树
    build_huffman_code(n);  // 哈夫曼树编码
    //输出已保存好的所有存在编码的哈夫曼编码
    for (i = 0; i < n; i++) {
        cout << huffman_nodes[i].value << ": Huffman code is: ";
        for (j = huffman_codes[i].start + 1; j < n; j++)
            cout << huffman_codes[i].bit[j];
        cout << endl;
    }
    return 0;
}