#include <iostream>
#include <vector>

int main () {
    system("chcp 65001");

    std::vector<int> ival;
    int val;
    while (std::cin >> val) {
        ival.push_back(val);
    }

    for (auto c : ival) {
        std::cout << c << " ";
    }

    std::cout << std::endl;
    /* #1
    for (int i = 0; i != ival.size() - 1; i ++) {
        int sum = ival[i] + ival[i + 1];
        std::cout << "第" << i << "和" << i + 1 << "的和为： " << sum << " ";
        std::cout << std::endl;
    }*/
    if (ival.size() % 2) {
        for (int i = 0; i != (ival.size() - 1) / 2; i++) {
            int sum = ival[i] + ival[ival.size() - i - 1];
            std::cout << "第" << i + 1 << "和" << ival.size() - i << "的和为： " << sum << " ";
            std::cout << std::endl;
        }
    } else {
        for (int i = 0; i != ival.size() / 2; i++) {
            int sum = ival[i] + ival[ival.size() - i - 1];
            std::cout << "第" << i + 1 << "和" << ival.size() - i  << "的和为： " << sum << " ";
            std::cout << std::endl;
        }
    }

    system("pause");
    return 0;
}