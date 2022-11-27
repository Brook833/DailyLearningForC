#include <iostream>

using namespace std;

int main () {
    auto sum = [](int a, int b){ return a + b; };
    cout << sum(2, 3) << endl;

    system("pause");
    return 0;
}