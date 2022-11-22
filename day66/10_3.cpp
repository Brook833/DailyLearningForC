#include <numeric>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> s;
    int i = 1;
    while (i != 101) {
        s.push_back(i);
        i++;
    }

    int sum = accumulate(s.cbegin(), s.cend(), 0);

    cout << sum << endl;

    system("pause");
    return 0;
}