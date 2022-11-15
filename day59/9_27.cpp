#include <iostream>
#include <forward_list>

using namespace std;

int main() {
    forward_list<int> l {1, 2, 3, 4, 5, 6, 7, 8, 9};


    auto prev = l.before_begin();
    auto now = l.begin();

    while (now != l.end()) {
        if (*now % 2) {
            now = l.erase_after(prev);
        } else {
            prev = now;
            now++;
        }
    }

    for (auto &c : l) {
        cout << c << " ";
    }

    system("pause");
    return 0;
}