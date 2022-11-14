#include <vector>
#include <list>
#include <iostream>

using namespace std;

int main () {
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    vector<int> v {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    list<int> l {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};




    vector<int>::iterator iv = v.begin();
    while (iv != v.end())
        if (!(*iv & 1))                // 偶数
            iv = v.erase(iv);        // 删除偶数，返回下一位置迭代器
        else
            ++iv;                      // 推进到下一位置

    for (auto &c : v) {
        cout << c << " ";
    }

    list<int>::iterator il = l.begin();
    while (il != l.end())
        if (*il & 1)                // 偶数
            il = l.erase(il);        // 删除偶数，返回下一位置迭代器
        else
            ++il;                      // 推进到下一位置

    cout << endl;
    for (auto &c : l) {
        cout << c << " ";
    }

    system("pause");
    return 0;
}