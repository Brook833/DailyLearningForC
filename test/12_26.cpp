#include <iostream>
#include <memory>

using namespace std;

int main() {
    size_t n(100);
    allocator<string> alloca;
    auto p = alloca.allocate(n);
    string s;
    string *q = p;
    while (cin >> s && q != p + n) {
        alloca.construct(q++, s);
    }

    const size_t size = q - p;

    for (size_t i = 0; i < size; i++) {
        cout << p[i] << endl;
    }

    while (q != p) {
        alloca.destroy(--q);
    }

    alloca.deallocate(p, n);

    system("pause");
    return 0;
}