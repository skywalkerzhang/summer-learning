#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
const int N = 1e2;

int main() {
    int n = 0;
    cin >> n;
    // 打印：算好空格，假如有n行，第n行有n个数字，有n-1个空格，那么每行都需要2n-1个位置
    int a[N + 1][N + 1];
    a[0][0] = 0;
    for (int i = 1; i < 3; i ++) {
        a[i][0] = 0;
        a[i][1] = 1;
        a[i][i] = 1;
        a[i][i + 1] = 0;
    }
    // 1; 1 1; 1 2 1; 1 3 3 1;
    for (int i = 3; i <= n; i ++) {
        a[i][0] = 0;
        for (int j = 1; j <= i; j ++) {
            a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= n; i ++) {
        // 输出空格
        for (int j = 1; j <= n - i; j ++) {
            cout << " ";
        }
        for (int j = 1; j <= i; j ++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }   
    return 0;
}