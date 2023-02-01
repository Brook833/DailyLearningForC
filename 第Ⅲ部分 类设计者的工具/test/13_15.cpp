#include <iostream>

using namespace std;

class numbered {
public:
    numbered() { mysn = c++; }
    numbered(const numbered&) : mysn(c++) {}
    int mysn;
private:
    static int c;
};

int numbered::c = 0;

void f (numbered s) { cout << s.mysn << endl; }

int main() {
    numbered a;      // 构造a时，c为0
    numbered b = a;  // 构造b时，c为1
    numbered c = b;  // 构造c时，c为2
    f(a);  // 3 传递参数时，c为3
    f(b);  // 4 同上
    f(c);  // 5 同上

    return 0;
}

