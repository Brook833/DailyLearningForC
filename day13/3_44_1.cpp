#include <iostream>

int main () {
    int ia[3][4];

    for (auto &c : ia) {
        for (auto &x : c) {
            x = rand() % 10;
        }
    }

    using int_arry = int[4];

    for (int_arry &c : ia) {
        for (auto x : c) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    system("pause");
    return 0;
}