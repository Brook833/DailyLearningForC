#include <iostream>
#include <string>
#include <memory>
#include <cstring>

using namespace std;

int main() {
    int size(0);
    cin >> size;  // 通过输入得到一个size值
    cin.ignore();
    char *p = new char[size + 1]();  // 动态分配内存，大小为给定值+1
    cout << size << endl;
    cin.get(p, size + 1);  // cin.get() 如果输入为abc则得到a
    cout << p << endl;

    delete [] p;

    system("pause");
    return 0;
}