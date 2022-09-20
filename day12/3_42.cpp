#include <iostream>
#include <vector>

int main () {
    system("chcp 65001");
    
    std::vector<int> ival(5);
    int arry[5];
    for (auto &c : ival) {
        c = rand() % 10;
    }
    
    std::cout << "初始数组值为：" << std::endl;

    for (auto c : ival) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i != 5; i++) {
        arry[i] = ival[i] + i;
    }
    
    std::cout << "数组2的值为 :" << std::endl;

    for (int i = 0; i != 5; i++) {
        std::cout << arry[i] << " ";
    }

    system("pause");
    return 0;

}