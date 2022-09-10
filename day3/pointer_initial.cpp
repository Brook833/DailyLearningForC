#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    int ival = 22;  
    
    int *pi1 = &ival; //pi1指向ival
    int *pi2 = pi1; //pi2指向ival
    cout << pi1 << endl;   
    cout << *pi1 << endl; 
    cout << pi2 << endl;
    cout << *pi2 << endl;
    int * *p = &pi1; //这样p才存放的是pi1的地址。
    cout << p;

   
    system("pause");
    return 0;
}