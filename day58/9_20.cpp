#include <iostream>
#include <list>
#include <deque>

using namespace std;

int main () {
    system("chcp 65001");

    list<int> value {2, 2, 4, 5, 7, 9};
    deque<int> v1, v2;

    for (auto &c : value) {
        if (c % 2) {
            v2.push_back(c);  // 存储偶数
        } else {
            v1.push_back(c);  // 存储奇数
        }
    }

    cout << "奇数：";
    for (auto &c : v1) {
        cout << c  << "  ";
    }
    cout << endl;

    cout << "偶数: ";
    for (auto &c : v2) {
        cout << c << "  ";
    }

    system("pause");
    return 0;
}