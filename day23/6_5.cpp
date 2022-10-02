#include <iostream>


int abs(int val) {
    if (val < 0) {
        return -val;
    }
    return val;
}
int main() {
    system("chcp 65001");

    int a;
    std::cin >> a;
    int abs_val = abs(a);
    std::cout << a << "的绝对值是:" << abs_val << std::endl;

    system("pause");
    return 0;
}