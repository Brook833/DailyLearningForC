#include <iostream>
#include <vector>

using namespace std;
vector<int>::iterator check(vector<int>::iterator a, vector<int>::iterator b, int c) {
  while (a != b) {
    if (*a == c) {
      return a;
    }
    a++;
  }
  return b;
}

int main() {

    vector<int> ilist = {1, 2, 3, 4, 5, 6, 7};

    cout << check(ilist.begin(), ilist.end(), 3) - ilist.begin() << endl;
    cout << check(ilist.begin(), ilist.end(), 8) - ilist.begin() << endl;

    system("pause");
    return 0;
}