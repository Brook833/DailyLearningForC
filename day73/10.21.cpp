#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  int sz = 5;
  auto reduec_sz = [&sz]() -> bool {
    if (sz == 0) {
      return 0;
    } else {
      sz--;
      return 1;
    }};

    while (reduec_sz()) {
      cout << sz << endl;
    }

    system("pause");
    return 0;
  }