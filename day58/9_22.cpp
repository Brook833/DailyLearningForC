#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> iv = {1, 1, 2, 1};
    int some_val = 1;

    vector<int>::iterator iter = iv.begin();
    int org_size = iv.size();  // 原容器大小
    int new_ele = 0;  // 新元素个数

    while (iter != (iv.begin() + org_size / 2 + new_ele)) {
        if (*iter == some_val) {
            iter = iv.insert(iter, 2 * some_val);
            ++new_ele;
            iter += 2;
        } else {
            ++iter;
        }
    }

    for (auto &c : iv) {
        cout << c << " ";
    }

    system("pause");
    return 0;
}