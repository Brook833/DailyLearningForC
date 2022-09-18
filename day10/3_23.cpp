#include <iostream>
#include <vector>

int main() {

    system("chcp 65001");
    std::vector<int> ival;
    //为ival添加10个元素，值为随机值
    for (int i = 0; i != 10; i++) {
 
        ival.push_back(rand() % 100);
    }
    //输出ival中每个元素的值
    std::cout << "随机出的十个数为: " << std::endl;
    for (auto c : ival) {
        std::cout << c << " ";
    }
    std::cout << std::endl << "他们加倍后为: " << std::endl;
    for (auto it = ival.begin(); it != ival.end(); it++) {
        *it = (*it) * 2;
        std::cout << *it << " ";
    }

    system("pause");
    return 0;
}