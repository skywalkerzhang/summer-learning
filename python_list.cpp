#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
template <class T>
class MyList{
    public:
        int size = 0;
    int initial_length = 16;
    T* arr = new T[initial_length];
    public:
        void append(T val){
            if (size > initial_length - 1) {
                // 需要扩容了
                resize();
            }
            arr[size ++] = val;
        }
        void resize(){
            initial_length *= 2;
            T* new_arr;
            new_arr = new T[initial_length];
            // 最后是要复制的字节数
            memcpy(new_arr, arr, size * sizeof(T));
            // delete[] rg -- 用来释放rg指向的内存，！！还逐一调用数组中每个对象的 destructor！！
            delete[] arr;
            arr = new_arr;
            cout << "resize the space!" << endl;
        }
        void print(){
            for (int i = 0; i < size; i ++){
                cout << arr[i] << " ";
            }
            cout << endl; 
        }
        void insert(int idx, T val){
            try{
                if (idx < 0) {
                    cout << "ERROR: idx < 0" << endl;
                    throw 99;
                }
                else if (idx > size){
                    cout << "ERROR: we do not support the idx > size" << endl;
                    throw 99;
                }
                if (size > initial_length - 1) {
                    resize();
                }
                for (int i = size; i > idx; i --) {
                    arr[i] = arr[i - 1];
                }
                arr[idx] = val;
                size ++;
            } catch (...) {
                cout << "INDEX ERROR! check your input!" << endl;
            }
        }
    void remove(int idx) {
        try{
            if (idx >= size) {
                cout << "idx > size!" << endl;
                throw 99;
            } else if (idx < 0){
                cout << "idx < 0" << endl;
                throw 99;
            }
            for (int i = idx; i < size; i ++) {
                arr[i] = arr[i + 1];
            }
            size --;
        } catch (...) {
            cout << "INDEX ERROR! double check your input!" << endl;
        }   
    }
    int operator[] (int idx){
        return this -> arr[idx];
    }
};

int main(){
    MyList<int> lst;
    for (int i = 0; i < 31; i ++){
        lst.append(i);
    }
    lst.print();
    lst.insert(1, 100);
    lst.insert(0, 99);
    lst.insert(-1, -1);
    lst.insert(33, 33);
    lst.insert(100, -100);
    lst.print();
    lst.remove(33);
    lst.remove(-1);
    lst.remove(33);
    lst.print();
    cout << lst[0] << endl;
    cout << "every is okay!" << endl;
    return 0; 
}