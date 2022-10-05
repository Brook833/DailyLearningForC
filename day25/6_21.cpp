#include <iostream>

using namespace std;
int cmp (const int a, const int *b) {
    if (a > *b) {
        return a;
    }
    return *b;
}

int main() {
    system("chcp 65001");

    int v1, v2;
    cin >> v1 >> v2;
    int *p = &v2;
    int result = cmp(v1, p);

    cout << "较大的值是:" << result << endl;
    system("pause");
    return 0;
}