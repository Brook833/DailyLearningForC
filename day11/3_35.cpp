#include <iostream>



int main () {
    system("chcp 65001");

    int arry[5] = {1, 2, 3, 4, 5};
    int *p = &arry[0];
    int *beg = std::begin(arry);
    int *e = std::end(arry);

    std::cout << "数组的初始值为:" << std::endl;

    for (auto c : arry) {
        std::cout << c << " ";
    }

    for (; p != e; p++) {
        *p = 0;
    }

    std::cout << std::endl << "修改后的值为:" << std::endl;

    for (auto c : arry) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    system("pause");
    return 0;
}