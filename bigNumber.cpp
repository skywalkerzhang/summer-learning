#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
class BigNumber {
    public:
        string val;
        BigNumber (string a) {
            this -> val = a;
        }
        BigNumber operator+ (BigNumber b) {
            int lengthA = this -> val.size();
            int lengthB = b.val.size();
            if (lengthA < lengthB){
                swap(lengthA, lengthB);
                swap(this -> val, b.val);
            }
            string res = "";
            int i = lengthB - 1;
            int pre = 0, cur = 0;
            for (int j = lengthA - 1; j >= 0; j --) {
                int valA = this -> val[j] - '0';
                int valB = 0;
                if (i != -1) {
                    valB = b.val[i --] - '0';
                }
                cur = (valA + valB + pre) % 10;
                res += (char)(cur + '0');
                pre = (valA + valB + pre) / 10;
            }
            if (pre != 0) {
                res += (char)(pre + '0');
            }
            reverse(res.begin(), res.end());
            return BigNumber(res);
        }

};

int main() {
    string inputA, inputB;
    cin >> inputA >> inputB;
    BigNumber a = BigNumber(inputA);
    BigNumber res = a + BigNumber(inputB);
    cout << res.val << endl;
    
    return 0;
}