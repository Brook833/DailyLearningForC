#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    list<int> s = {0, 2, 4, 5, 6, 7, 8, 0, 9};
    auto it = find(s.rbegin(), s.rend(), 0);
    cout << *it << "is front of" << *it.base();

    system("pause");
    return 0;
}