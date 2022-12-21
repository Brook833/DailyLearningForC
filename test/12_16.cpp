#include <iostream>
#include <memory>

using namespace std;

int main() {
    unique_ptr<int> up(new int(42));
    // unique_ptr<int> up2 = up;
    // unique_ptr<int> up3(up);

    return 0;
}