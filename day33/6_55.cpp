#include <iostream>
#include <vector>

using namespace std;

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

int div2(int a, int b) {
    return a / b;
}

void compute(int a, int b, int(*p)(int, int)) {
    cout << p(a, b) << endl;
}

int main() {
    decltype(add) *p1 = add, *p2 = sub, *p3 = mul, *p4 = div2;
    vector<decltype(add) *> p = {p1, p2, p3, p4};
    for (auto c : p) {
        compute(3, 5, c);
    }

    system("pause");
    return 0;
}
