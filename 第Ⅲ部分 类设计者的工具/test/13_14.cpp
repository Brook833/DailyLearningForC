#include <iostream>

using namespace std;

class numbered {
public:
    numbered() { mysn = c++; }
    int mysn;
private:
    static int c;
};

int numbered::c = 0;

void f (numbered s) { cout << s.mysn << endl; }

int main() {
    numbered a , b = a, c = b;
    f(a);  // 0 构造a时，c为0
    f(b);  // 0 构造b时，c为1，但编译器生成的合成赋值函数，将a的mysn直接赋值给了b，因此也是0
    f(c);  // 0 同b

    return 0;
}

