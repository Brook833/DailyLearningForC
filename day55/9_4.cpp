#include <iostream>
#include <vector>

using namespace std;
bool check(vector<int>::iterator a, vector<int>::iterator b, int c) {
  while (a != b) {
    if (*a == c) {
      return true;
    }
    a++;
  }
  return false;
}

int main() {
  system("chcp 65001");
  vector<int> ilist = {1, 2, 3, 4, 5, 6, 7};

  cout << check(ilist.begin(), ilist.end(), 3) << endl;
  cout << check(ilist.begin(), ilist.end(), 8) << endl;


  system("pause");
  return 0;
}