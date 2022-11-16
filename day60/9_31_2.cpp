#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> l {1, 2, 3, 4, 5, 6, 7, 8 , 9};
    auto now = l.begin();

    while (now != l.end()) {
        if (*now % 2) {
            now = l.insert(now, *now);
            now++;
            now++;
        } else {
            now = l.erase(now);
        }
    }

    for (auto c : l) {
        cout << c << " ";
    }

    system("pause");
    return 0;
}