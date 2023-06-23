#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
// 要考虑负数
class BigNumber {
    public:
        string val;
        bool isPos;
        BigNumber (string a) {
            if (a[0] == '-') {
                this -> isPos = false;
                this -> val = a.substr(1, a.size());
            } else {
                this -> isPos = true;
                this -> val = a;
            }
        }
        // 保证传进来的都是正数
        // 数据合法性在最外层做，这里不考虑了，这里认为a,b一定合法
        string add (string a, string b) {
            int lengthA = a.size();
            int lengthB = b.size();
            if (lengthA < lengthB){
                swap(lengthA, lengthB);
                swap(a, b);
            }
            string res = "";
            int i = lengthB - 1;
            int pre = 0, cur = 0;
            for (int j = lengthA - 1; j >= 0; j --) {
                int valA = a[j] - '0';
                int valB = 0;
                if (i != -1) {
                    valB = b[i --] - '0';
                }
                cur = (valA + valB + pre) % 10;
                res += (char)(cur + '0');
                pre = (valA + valB + pre) / 10;
            }
            if (pre != 0) {
                res += (char)(pre + '0');
            }
            reverse(res.begin(), res.end());
            return res;
        }

        string substract(string a, string b) {
            int lengthA = a.size();
            int lengthB = b.size();
            int pre = 0, cur = 0;
            bool isSwap = false;
            // 比长度比大小，把大的放在前面
            if (lengthA < lengthB || (lengthA == lengthB) && a < b) {
                swap(lengthA, lengthB);
                swap(a, b);
                isSwap = true;
            }
            int i = lengthB - 1;
            string res = "";
            for (int j = lengthA - 1; j >= 0; j --) {
                if (i >= 0) {
                    cur = (a[j] - '0') - (b[i --] - '0') - pre;
                } else {
                    cur = (a[j] - '0') - pre;
                }
                if (cur < 0) {
                    cur += 10;
                    pre = 1;
                } else {
                    pre = 0;
                }
                res += (char)(cur + '0');
            }
            // 消除前导0
            reverse(res.begin(), res.end());
            int zeroIdx = 0;
            while(zeroIdx < res.size() && res[zeroIdx ++] != '0');
            if (zeroIdx == res.size()) {
                res = "0";
            } else {
                res = res.substr(zeroIdx, res.size());
            }
            return (isSwap ? "-" : "") + res; 
        }

        string multipy(string a, string b) {
            if (a == "0" || b == "0") {
                return "0";
            }
            int cur = 0, pre = 0;
            int lengthA = a.size(), lengthB = b.size();
            if (lengthA < lengthB) {
                swap(lengthA, lengthB);
                swap(a, b);
            }
            string preRes = "", curRes = "";
            for (int i = lengthB - 1; i >= 0; i --) {
                pre = 0;
                curRes = "";
                for (int j = lengthA - 1; j >= 0; j --) {
                    cur = (a[j] - '0') * (b[i] - '0') + pre;
                    pre = cur / 10;
                    cur %= 10;
                    curRes += (char)(cur + '0');
                }
            
                if (pre != 0) {
                    curRes += (char)(pre + '0');
                } 

                reverse(curRes.begin(), curRes.end());
                for (int k = 0; k < lengthB - i - 1; k ++)
                    curRes += '0';
                if (preRes != "") {
                    curRes = add(preRes, curRes);
                }
                preRes = curRes;
            }
            // 和加减法不一样，乘法不用再多算一次进位了，乘法实现不是按照进位 而是按照循环，底层逻辑不一样
            return curRes;
        }
        
        BigNumber operator+ (BigNumber b) {
            if (this -> isPos && b.isPos) {
                return BigNumber(add(this -> val, b.val));
            } else if(!this -> isPos && !b.isPos) {
                return BigNumber("-" + add(this -> val, b.val));
            } else if(this -> isPos, !b.isPos) {
                return BigNumber(substract(this -> val, b.val));
            } else if (!this -> isPos && b.isPos) {
                return BigNumber(substract(b.val, this -> val));
            }
            return BigNumber("-0");
        }

        BigNumber operator- (BigNumber b) {
            if (this -> isPos && b.isPos) {
                return BigNumber(substract(this -> val, b.val));
            } else if(!this -> isPos && !b.isPos) {
                // -a - (-b) = -a + b = b - a
                return BigNumber(substract(b.val, this -> val));
            } else if(this -> isPos, !b.isPos) {
                // a - (-b) = a + b
                return BigNumber(add(this -> val, b.val));
            } else if (!this -> isPos && b.isPos) {
                // -a - b = - (a + b)
                return BigNumber("-" + add(b.val, this -> val));
            }
            return BigNumber("-0");
        }

        BigNumber operator* (BigNumber b) {
            string retVal = multipy(this -> val, b.val);
            if (this -> isPos ^ b.isPos) {
                return BigNumber("-" + retVal);
            } 
            return BigNumber(retVal);
        }
};

// 重载iostream不可以写在类里面
ostream& operator<< (ostream& out, BigNumber& a) {
    // 注意 << 运算级高于三目运算符
    out << (a.isPos ? a.val : '-' + a.val);
    return out;
}

int main() {
    string inputA, inputB;
    cin >> inputA >> inputB;
    BigNumber a = BigNumber(inputA);
    BigNumber b = BigNumber(inputB);
    BigNumber addRes = a + b;
    BigNumber subRes = a - b;
    BigNumber mulRes = a * b;
    cout << addRes << " " << subRes << " " << mulRes << endl;

    return 0;
}
