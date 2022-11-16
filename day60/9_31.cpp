#include <iostream>
#include <forward_list>
#include <list>

using namespace std;

int main() {
    forward_list<int> l {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto now = l.begin();
    auto prev = l.before_begin();

    while(now != l.end()) {
        if (*now % 2) {
            now = l.insert_after(now, *now);
            prev = now;
            now++;
        } else {
            now = l.erase_after(prev);
        }
    }

    for (auto &c : l) {
        cout << c << " ";
    }
    system("pause");
    return 0;
}