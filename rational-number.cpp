// 构造有理数，有理数是整数和分数组成的集合
// 要求 构造一个类型代表有理数
// 可以将它转换为小数，可以进行加减乘除运算，可以打印内容，以x / y 的方式展示，要求展示内容为最简形式

// 如果有可能，可以同时实现一个大整数并运用到有理数类型上使得它可以支持大分数

#include <stdio.h>
#include <iostream>
using namespace std;

// 这里需要考虑负数的余数问题
// 正余数 or 负余数？
// c++遵循了商靠近0的原则，即5%(-3) 的结果为2而不是-1，(-5)%3的结果是-2而不是1。
int getGCD(int x, int y) {
    // TODO：考虑负数
    // 正余数 - 负余数 = 被余数，简化问题，传进来的时候分子已经被整理为负数（不影响结果）
    try{
        if (y <= 0){
            throw 99;
        }
        return x % y == 0 ? y : getGCD(y, x % y > 0 ? (x % y) : (x % y) + y);
    }
    catch(...){
        cout << "y should bigger than 0!" << endl;
        exit(0);
    }
    return -1;
}
int getLCM(int x, int y) {
    return x * y / getGCD(x, y);
}
int getLCM(int x, int y, int gcd) {
    return x * y / gcd;
}

// 解藕
// int getLCM(int x, int y, int gcd) { return x * y / gcd; }
// int getLCM(int x, int y) { return getLCM(x, y, getGCD(x, y)); }

class RationalNumber {
    public:
        int numerator;
        int denominator;
        
    RationalNumber () {

    }

    RationalNumber (int x, int y) {
        // 整理为同格式
        // 保证分母是正的话运算会比较简单
        if (x < 0 && y < 0 || x > 0 && y < 0) {
            x *= -1;
            y *= -1;
        }
        // 好像这里失效了？
        this -> numerator = x;
        this -> denominator = y;
    }

    RationalNumber simplify(RationalNumber x) {
        if (x.numerator < 0 && x.denominator < 0 || x.numerator > 0 && x.denominator < 0) {
            x.numerator *= -1;
            x.denominator *= -1;
        }
        int gcd = getGCD(x.numerator, x.denominator);
        x.denominator /= gcd;
        x.numerator /= gcd;
        return x;
    }
    RationalNumber simplify() {
        if (this -> numerator < 0 && this -> denominator < 0 || this -> numerator > 0 && this -> denominator < 0) {
            this -> numerator *= -1;
            this -> denominator *= -1;
        }
        int gcd = getGCD(this -> numerator, this -> denominator);
        this -> denominator /= gcd;
        this -> numerator /= gcd;
        // 反向操作
        // int a = 5, int *p = &a; 这里*表示一级指针
        // *this这里*表示解引用
        return *this;
    }
    RationalNumber operator+ (RationalNumber y) {
        RationalNumber res;
        res.denominator = getLCM(this -> denominator, y.denominator);
        res.numerator = this -> numerator * res.denominator / this -> denominator + y.numerator * res.denominator / y.denominator;
        return simplify(res);
    }
    RationalNumber operator- (RationalNumber y) {
        RationalNumber res;
        res.denominator = getLCM(this -> denominator, y.denominator);
        res.numerator = this -> numerator * res.denominator / this -> denominator - y.numerator * res.denominator / y.denominator;
        return simplify(res);
    }
    RationalNumber operator* (RationalNumber y) {
        RationalNumber res;
        res.denominator = this -> denominator * y.denominator;
        res.numerator = this -> numerator * y.numerator; 
        return simplify(res);
    }
    RationalNumber operator/ (RationalNumber y) {
        RationalNumber res;
        res.denominator = this -> denominator * y.numerator;
        res.numerator = this -> numerator * y.denominator; 
        return simplify(res);
    }
    double getPoint(){
        return (double)this -> numerator / this -> denominator; 
    }
    void print() {
        RationalNumber res = simplify();
        if (res.denominator == 1) {
            cout << res.numerator << endl;
        } else {
            cout << res.numerator << " / " << res.denominator << endl;
        }
    }
};

int main() {
    int numerator = 0, denominator = 0;
    cin >> numerator >> denominator;
    RationalNumber x = RationalNumber(numerator, denominator);
    // x = x.simplify(x);
    // cout << x.numerator << " / " << x.denominator << endl;
    x.print();
    return 0;
}
