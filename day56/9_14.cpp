#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

int main() {
  list<char *> a = {"hello", "world", "!"};
  vector<string> b;

  b.assign(a.begin(), a.end());

  for (auto &c : b) {
    cout << c << endl;
  }

  system("pause");
  return 0;
}