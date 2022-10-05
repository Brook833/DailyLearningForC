#include <iostream>

using namespace std;

void change(int *&p, int *&q) {
    int *tmp;
    tmp = p;
    p = q;
    q = tmp;
}

int main(){
    system("chcp 65001");
    int a = 10, b = 30;
    int *p = &a;
    int *q = &b;

    cout << "交换之前：" << p << " = " << *p << " " << q << " = " << *q << endl;
    change(p , q);
    cout << "交换之后：" << p << " = " << *p << " " << q << " = " << *q << endl;
  
    system("pause");
    return 0;
}