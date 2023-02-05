#include <iostream>
#include <vector>

using namespace std;

class X {
public:
    X() { cout << "构造函数: X()" << endl; }
    X(const X&) { cout << "拷贝构造函数: X(const X&)" << endl; }
    X& operator=(X& rhs) {
        cout << "拷贝运算符: =(const X&)" << endl;
        return *this;
    }
    ~X() { cout << "析构函数: ~X()" << endl; } 
};

void f1(X x) {}
void f2(X &x) {}

int main() {
    cout << "1局部变量: X x  ";
    X x;
    cout << endl;

    cout << "2非引用参数传递: f1(x)  ";
    f1(x);
    cout << endl;

    cout << "3引用参数传递: f2(x)  ";
    f2(x);
    cout << endl;

    cout << "4动态分配: X *px = new X  ";
    X *px = new X;
    cout << endl;
    
    cout << "5添加到容器中: vx.push_back(x)  ";
    vector<X> vx;
    vx.push_back(x);
    cout << endl;

    cout << "6释放动态分配对象: delete px  ";
    delete px;
    cout << endl;

    cout << "7拷贝初始化和赋值: y = x  ";
    X y = x;
    y = x;
    cout << endl;

    return 0;
}

/*
1局部变量: X x  构造函数: X()

2非引用参数传递: f1(x)  拷贝构造函数: X(const X&)
析构函数: ~X()

3引用参数传递: f2(x)  
4动态分配: X *px = new X  构造函数: X()

5添加到容器中: vx.push_back(x)  拷贝构造函数: X(const X&)

6释放动态分配对象: delete px  析构函数: ~X()

7拷贝初始化和赋值: y = x  拷贝构造函数: X(const X&)
拷贝运算符: =(const X&)

析构函数: ~X()  y
析构函数: ~X()  vx的第一个元素
析构函数: ~X()  x
*/