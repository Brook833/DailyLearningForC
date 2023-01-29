#include <string>

using namespace std;

class HasPtr {
 public:
  HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}  // 初始化
  HasPtr(const HasPtr &);  // 拷贝构造函数

 private:
  string *ps;
  int i;
};

HasPtr::HasPtr(const HasPtr &orig) : ps(new string(*orig.ps)), i(orig.i) {}