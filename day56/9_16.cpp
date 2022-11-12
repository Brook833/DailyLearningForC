#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main () {
    system("chcp 65001");
    
    list<int> a {1, 3, 5, 7};
    vector<int> b {1, 3, 5, 7};

    if (a.size() != b.size()) {
        cout << "不相等" << endl;
    }

auto it = b.begin();
    for (auto &c : a) {
        if (c != *it) {
            cout << "不相等" << endl;
        }
        it++;
    }

    cout << "相等" << endl;

    system("pause");
    return 0;
}