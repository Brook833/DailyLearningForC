#include <iostream>

int main() {
    system("chcp 65001");

    int i = 8;
    double d = 5.20;

    int result = i * static_cast<int>(d);

    std::cout << result << std::endl;

    system("pause");
    return 0;
}

/*
a: pv = static_cast<void *>(const_cast<string *>(ps));
b: i = static_cast<int>(*pc);
c: pv = static_cast<void*>(&d);
d: pc = static_cast<char *>(pv);

*/