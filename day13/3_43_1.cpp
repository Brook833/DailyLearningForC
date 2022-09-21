#include <iostream>

int main () {
    int ia[3][4];

    for (auto &c : ia) {
        for (auto &x : c) {
            x = rand() % 10;
        }
    }

    for (int (&c)[4] : ia) {
        for (auto x :c) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    system("pause");
    return 0;
}