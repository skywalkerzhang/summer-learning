#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
const int N = 1e5;
int change_dimension(int i, int j) {
    int pos = 0;
    for (int idx = 1; idx <= i; idx ++) {
        pos += idx * idx;
    }
    pos += j;
    return pos;
}

int main() {
    int n = 0;
    cin >> n;
    // 打印：算好空格，假如有n行，第n行有n个数字，有n-1个空格，那么每行都需要2n-1个位置
    int a[N + 1];
    memset(a, 0, (n + 1) * sizeof(int));
    for (int i = 1; i < 3; i ++) {
        for (int j = 1; j <= i; j ++) {
            int pos = change_dimension(i, j);
            a[pos] = 1;
        }
    }
    // 1; 1 1; 1 2 1; 1 3 3 1;
    for (int i = 3; i <= n; i ++) {
        for (int j = 1; j <= i; j ++) {
            int right = change_dimension(i - 1, j), left = change_dimension(i - 1, j - 1);
            int cur = change_dimension(i, j);
            a[cur] = a[left] + a[right];
        }
    }

    for (int i = 1; i <= n; i ++) {
        // 输出空格
        for (int j = 1; j <= n - i; j ++) {
            cout << " ";
        }
        for (int j = 1; j <= i; j ++) {
            int pos = change_dimension(i, j);
            cout << a[pos] << " ";
        }
        cout << endl;
    }   
    return 0;
}