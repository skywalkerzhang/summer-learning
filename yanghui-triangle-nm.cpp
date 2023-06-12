#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
const int N = 1e5;
int findVal(int i, int j){
    if (i <= 0 || j <= 0) {
        return 0;
    }
    if (j > i) {
        return 0;
    }
    if (i == 1 || i == 2) {
        return 1;
    }
    return findVal(i - 1, j) + findVal(i - 1, j - 1);
}
int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    cout << findVal(n, m) << endl;
    return 0;
}