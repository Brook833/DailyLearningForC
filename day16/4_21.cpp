#include <iostream>
#include <vector>

int main() {
    system("chcp 65001");
    std::vector<int> i(20);
    for (auto &c : i) {
        c = rand() % 100;
    }

    std::cout << "初始值为: " << std::endl;

    for (auto c : i) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    for (auto &c : i) {
        c = ((c % 2) ? (c * 2) : c);
    }

    std::cout << "奇数值翻倍后为: " << std::endl;

    for (auto c : i) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    system("pause");
    return 0;
}