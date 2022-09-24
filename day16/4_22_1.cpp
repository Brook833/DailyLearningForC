#include <iostream>

int main() {
    system("chcp 65001");
    int grade;
    std::cin >> grade;
    auto finalgrade = ((grade > 100) ? "输入错误" :
                                    ((grade > 90) ? "high pass" : 
                                    ((grade > 75) ? "low pass" :
                                    ((grade > 60) ? "pass" : "fail"))));
    std::cout << "该学生得分为:" << grade << " 老师评语为:" << finalgrade << std::endl;
    system("pause");
    return 0;
}