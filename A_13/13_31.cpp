#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

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
  bool operator< (const HasPtr &h) const {
    return *B < *h.B;
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
  cout << "交换 " << *lhs.B << " 和 " << *rhs.B << endl;
  swap(lhs.A, rhs.A);
  swap(lhs.B, rhs.B);
  cout << "swap:" << endl;
}

int main(int argc, char **argv) {
    ifstream in(argv[1]);
    vector<HasPtr> vec;
    string line;
    string word;
    while (getline(in, line)) {
        istringstream l_in(line);
        while (l_in >> word) {
            vec.push_back(word);
        }
    }

    for (auto p : vec) {
        cout << *p << " ";
    }
    cout << endl;

    sort(vec.begin(), vec.end());

    for (auto p : vec) {
        cout << *p << " ";
    }
    cout << endl;
    
    return 0;
}