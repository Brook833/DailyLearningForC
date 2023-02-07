#include <iostream>
#include <string>

using namespace std;

class HasPtr {
 public:
  HasPtr(const std::string &s = std::string())
      : ps(new std::string(s)), i(0), use(new int(1)) {}
  HasPtr(const HasPtr &h) : ps(h.ps), i(h.i), use(h.use) { ++*use; }
  HasPtr &operator=(const HasPtr &rhs) {
    ++*rhs.use;
    if (--*use == 0) {
      delete ps;
      delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
  }
  HasPtr &operator=(const string &s) {
    *ps = s;
    return *this;
  }
  string &operator*() { return *ps; }

  ~HasPtr() {
    if (--*use == 0) {
      delete ps;
      delete use;
    }
  }

 private:
  string *ps;
  int i;
  int *use;
};

int main() {
  HasPtr h("hi mom!");
  HasPtr h2 = h;  // 未分配新 string，h2 和 h 指向相同的 string
  h = "hi dad!";
  cout << "h: " << *h << endl;  // h: hi dad!
  cout << "h2: " << *h2 << endl;  // h2: hi dad!
  return 0;
}