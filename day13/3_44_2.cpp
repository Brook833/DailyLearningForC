#include <iostream>

int main () {
    int ia[3][4];

    for (auto &c : ia) {
        for (auto &x : c) {
            x = rand() % 10;
        }
    }

    for (int i = 0; i != 3; i++) {
        for (int j = 0; j != 4; j++) {
            std::cout << ia[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    system("pause");
    return 0;
}