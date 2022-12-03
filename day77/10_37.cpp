#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <list>

using namespace std;

int main() {
    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    auto r_it = vec.rbegin() + 3;
    auto r_end = vec.rend() - 2;
    list<int> l(r_it, r_end);

    for (auto c : l) {
        cout << c << endl;
    }

    system("pause");
    return 0;
}