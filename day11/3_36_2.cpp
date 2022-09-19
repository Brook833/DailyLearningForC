#include <iostream>

int main () {
    system ("chcp 65001");

    int arry1[5];
    int arry2[5];
    int val;
    
    for (int i = 0; i != 5; i++) {
        arry1[i] = rand() % 10;
    }

    std::cout << "请输入您猜测的5个数字:" << std::endl;

    for (int i = 0; i != 5; i++) {
        if (std::cin >> val) {
            arry2[i] = val;
        }
    }
    
    std::cout << "您输入的5个数字是:" << std::endl;

    for (auto c : arry2) {
        std::cout << c << " ";
    }

    std::cout << std::endl << "系统数据是:" << std::endl;

    for (auto c : arry1) {
        std::cout << c << " ";
    }

    std::cout << std::endl;
    
    int *p = std::begin(arry1), *q = std::begin(arry2);

    for (; p != std::end(arry1) && q != std::end(arry2); p++, q++) {
        if (*p != *q) {
            std::cout << "您猜测有误" << std::endl;
            system("pause");
            return 0;
        } else {
            continue;
        }
    }

    std::cout << "恭喜您，所有数据全部正确!!!" << std::endl;

    system("pause");
    return 0;

}