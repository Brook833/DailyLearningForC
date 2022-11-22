#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int main () {
    vector<int> ivec = {1, 2, 3, 4, 5, 6, 6, 6, 2};
    auto n = count(ivec.begin(), ivec.end(), 6);
    cout << n << endl;

    system("pause");
    return 0;
}