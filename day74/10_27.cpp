#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int main () {
    vector<int> i = {1, 5, 7, 3, 4 ,5};
    list<int> i2;
    sort(i.begin(), i.end());
    unique_copy(i.begin(), i.end(), back_inserter(i2));

    for (auto c : i2) {
        cout << c << " ";
    }
    
    system("pause");
    return 0;
}