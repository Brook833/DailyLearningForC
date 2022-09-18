#include <iostream>
#include <vector>

int main () {
    system("chcp 65001");
    
    std::vector<int> vInt;
    int val;

    while (std::cin >> val) {
        vInt.push_back(val);
    }

    std::cout << "输入的值为: " << std::endl;

    for (auto c : vInt) {
        std::cout << c << " ";
    }

    /* #1
    std::cout << std::endl << "两两之和分别为: " << std::endl;
    for (auto it = vInt.begin(); it != vInt.end() - 1; it++) {
        auto sum = (*it) + (*(it + 1));
        std::cout << sum << " ";
    }*/

    std::cout << std::endl << "首尾两两之和为: " << std::endl;
    
    if (vInt.size() % 2) {
        for (auto it = vInt.begin(); it != vInt.begin() + (vInt.size() / 2); it++) {
            
            auto sum = (*it) + (*(vInt.begin() + (vInt.end() - it) - 1));
            std::cout << sum << " ";
        }
    }

    system("pause");
    return 0;
}