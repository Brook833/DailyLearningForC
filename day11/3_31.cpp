#include <iostream>
#include <vector>

int main () {
    system("chcp 65001");
    int arry[10];
    std::vector<int> arry2;
    for (int i = 0; i != 10; i++) {
        arry[i] = i;
    }

    for (int i = 0; i != 10; i++) {
        arry2.push_back(arry[i]);
    }
    std::cout << "数组1的元素值为： " << std::endl;
    for (auto c : arry) {
        std::cout << c << " ";
    }

    std::cout << "数组2的元素值为： " << std::endl;

    for (auto c : arry2) {
        std::cout << c << " ";
    }


    system("pause");
    return 0;
}