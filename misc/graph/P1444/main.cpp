#include <iostream>
#include <algorithm>

using namespace std;
#define N 30

struct node {
    int x, y;

    bool operator<(const node o) const {
        return y < o.y || (y == o.y && x < o.x);
    }
};

node a[N];

int f(int num, int d, int begin, int pl) {

}

bool check() {
    if (int j = 1;j <= n;
    j++)
    if ()
}

void dfs(int x) {

}

int
main() {
    int n;
    int x, y;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a + 1, a + n + 1);
    dfs(1);


}