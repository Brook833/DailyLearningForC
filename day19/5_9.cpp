#include <iostream>

using namespace std;

int main() {
  system("chcp 65001");

  uint32_t number = 0;
  char s;
  while (cin >> s) {
    if (s == 'a') {
      ++number;
    } else if (s == 'e') {
      ++number;
    } else if (s == 'i') {
      ++number;
    } else if (s == 'o') {
      ++number;
    } else if (s == 'u') {
      ++number;
    } else {
      ;
    }
  }
  cout << "输入共有" << number << "个元音字母" << endl;

  system("pause");
  return 0;
}