#include <iostream>
#include <windows.h>
using namespace std;
int global_int;
int main()
{
    /* 列表初始化
    long double ld = 3.14159265358;
    int a{ld};*/

    /* 默认初始化 
    int local_int; 
    cout << a << endl;
    按照书中描述，global_int = 0; local_int 的值未定义。
    在gcc7.3中测试，发现local_int的值也为0，应该是编译器的扩展导致，与C++无关。
    ,应该是gcc自身扩展*/

    system("pause");
    return 0;
}
