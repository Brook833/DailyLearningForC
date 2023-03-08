#include <iostream>

template <typename T>
T compare(const T &v1, const T &v2) {
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

int main() {
    system("chcp 65001");
    auto i = compare(10, 8);
    auto f = compare(18.88, 8.88);

    std::cout << i << std::endl;
    std::cout << f << std::endl;
    system("pause");
    return 0;
}