#include <iostream>
#include <algorithm>

using namespace std;

int
main() {
    // 数位上 最低有效位
    // a与-a
    // a   011011000
    // ~a  100100111
    //~a+1 100101000
    // &   000001000

    int a = 3;
    int last_one = 0;
    last_one = a & (~a + 1);
    cout << last_one << endl;

    last_one = a & (-a);
    cout << last_one << endl;
}