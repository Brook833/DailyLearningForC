#include <iostream>
#include <vector>

int main() {
    system("chcp 65001");

    std::vector<unsigned> scores(11);
    unsigned grade;
    auto it = scores.begin();
    while (std::cin >> grade) {
        if (grade <= 100) {
            ++(*(it + grade / 10));
        }
    }
    std::cout << "共输入了" << scores.size() << "个成绩" << std::endl;
    std::cout << "各分数段人数分布是(成绩由低到高) :" << std::endl;

    for (; it != scores.end(); it++) {
        std::cout << *it << " ";
    }

    system("pause");
    return 0;
    
}