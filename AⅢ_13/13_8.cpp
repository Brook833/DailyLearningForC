#include <string>

using namespace std;

class HasPtr {
 public:
  HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}  // 初始化
  HasPtr(const HasPtr &);  // 拷贝构造函数
  HasPtr &operator=(HasPtr &);  // 拷贝赋值运算符

 private:
  string *ps;
  int i;
};

HasPtr::HasPtr(const HasPtr &orig) : ps(new string(*orig.ps)), i(orig.i) {}

HasPtr& HasPtr::operator=(HasPtr &rhs) {
    string *newps = new string(*rhs.ps);  // 拷贝指针指向的对象
    delete ps;  // 销毁原string
    ps = newps;  // 指向新string
    i = rhs.i;  // 使用内置的int赋值
    return *this;  // 返回一个此对象的引用
}