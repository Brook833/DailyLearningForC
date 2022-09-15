#include <iostream>
#include <windows.h>

using namespace std;

int main() {

    int year = 2022;
    int month = 10;
    int *pi = &year;
    system("chcp 65001"); //解决cout中有中文时，输出乱码的情况。
    cout << "今年是" << *pi << "年" << endl;
    *pi = 2050;
    cout << "全面建成小康社会是在" << *pi << "年" << endl;
    pi = &month;
    cout << "国庆节是在" << *pi << "月" << endl;
    system("pause");

    return 0;
}