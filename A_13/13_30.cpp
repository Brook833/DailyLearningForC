#include <iostream>
#include <string>

using namespace std;

class HasPtr {
 public:
  friend void swap(HasPtr &lhs, HasPtr &rhs);

 public:
  HasPtr(const string &s = string()) : A(0), B(new string(s)) {}  // 构造函数
  HasPtr(const HasPtr &h) : A(h.A), B(new string(*h.B)) {}  // 拷贝构造函数
  HasPtr &operator=(const HasPtr &h) {  // 拷贝赋值运算符
    string *p = new string(*h.B);
    delete B;
    B = p;
    A = h.A;
    return *this;
  }
  HasPtr &operator=(const string &s) {  // 赋予新string
    *B = s;
    return *this;
  }
  string &operator*() {  // 解引用
    return *B;
  }
  ~HasPtr() { delete B; }  // 析构函数
 private:
  int A;
  string *B;
};

void swap(HasPtr &lhs, HasPtr &rhs) {
  using std::swap;
  swap(lhs.A, rhs.A);
  swap(lhs.B, rhs.B);
  cout << "swap:" << endl;
}

int main() {
    HasPtr h("hi mom!");
    HasPtr h2(h);       // 行为类值，h2、h3 和 h 指向不同 string
    HasPtr h3 = h;
    h2 = "hi dad!";
    h3 = "hi son!";
    swap(h2, h3);  // swap
    cout << "h: " << *h << endl;  // hi mom！
    cout << "h2: " << *h2 << endl;  // hi son！
    cout << "h3: " << *h3 << endl;  // hi dad！
    system("pause");
    return 0;
}