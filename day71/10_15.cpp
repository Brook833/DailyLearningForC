#include <iostream>

using namespace std;

void add_4(int a) {
    auto sum = [a](int b){ return a + b; };
    cout << sum (4) << endl;
}

int main() {
    add_4(2);
    add_4(3);

    system("pause");
    return 0;
}