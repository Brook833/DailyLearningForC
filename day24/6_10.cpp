#include <iostream>

void change(int *p, int *q) {
    int tmp = *p;
    *p = *q;
    *q = tmp;
    std::cout << *p << "  " << *q << std::endl;
}

int main() {
    int a = 5;
    int b = 10;
    change(&a, &b);

    system("pause");
    return 0;
}