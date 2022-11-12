#include <vector>
#include <iostream>


using namespace std;
int main() {
    system("chcp 65001");

    vector<int> a {1, 3, 5, 7};
    vector<int> b {1, 3, 5, 7};

    if (a == b) {
        cout << "两个vector<int>容器相等" << endl;
    } else {
        cout << "两个vector<int>容器不等" << endl;
    }

    system("pause");
    return 0;
}