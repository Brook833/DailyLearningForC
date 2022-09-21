#include <iostream>

int main () {
    int ia[3][4];
    for (auto &c : ia) {
        for (auto &x : c) {
            x = rand() % 10;
        }
    }


    for (int (*p)[4] = ia; p != ia + 3; p++) {
        for (int *q = *p; q != *p + 4; q++) {
            std::cout << *q << " ";
        }
        std::cout << std::endl;
    }

    system("pause");
    return 0;
}