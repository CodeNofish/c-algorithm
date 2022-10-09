#include <iostream>
#include <algorithm>

using namespace std;
#define N 5
#define W 6
struct Wheel {
    int speed, num, start[W], len[W];
};
Wheel wheels[N];

int gap[360];   // 表示齿孔

int
main() {
    for (int i = 0; i < N; i++) {
        cin >> wheels[i].speed;
        cin >> wheels[i].num;
        for (int j = 0; j < wheels[i].num; j++) {
            cin >> wheels[i].start[j];
            cin >> wheels[i].len[j];
        }
    }
    // 模拟一轮时间
    for (int t = 0; t < 360; t++) {
        // 初始化间隙
        for (int i = 0; i < 360; i++)
            gap[i] = 0;
        // 模拟轮子状态，求出间隙出现次数
        for (int i = 0; i < N; i++) {
            int speed = wheels[i].speed, num = wheels[i].num;
            for (int j = 0; j < num; j++) {
                int start = wheels[i].start[j], len = wheels[i].len[j];
                for (int k = 0; k <= len; k++)
                    gap[(start + k) % 360]++;
                wheels[i].start[j] = (start + speed) % 360;
            }
        }
        // 该间隙 同时出现5次
        for (int i = 0; i < 360; i++) {
            if (gap[i] == N) {
                cout << t;
                return 0;
            }
        }
    }
    cout << "none";
}