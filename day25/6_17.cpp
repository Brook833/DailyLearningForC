#include <cctype>
#include <iostream>
#include <string>

using namespace std;

bool Xstring(const string& s) {
  for (auto c : s) {
    if (isupper(c)) {
      return true;
    }
  }
  return false;
}

void changeS(string& s) {
    for (auto &c : s) {
        c = tolower(c);
    }
}

int main() {
    system("chcp 65001");
    string s ("World");

    if (Xstring(s)) {
        changeS(s);
    }

    for (auto c : s) {
        cout << c;
    }
    cout << endl;
    
    system("pause");
    return 0;
}
//6_18_a: bool compare(const matrix& a, const matrix& b);
//6_18_b: vector<int>::iterator change_val(int a, vector<int>::iterator);