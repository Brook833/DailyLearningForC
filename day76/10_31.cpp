#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    istream_iterator<int> cin_iter(cin), eof;
    vector<int> vec;
    while (cin_iter != eof) {
        vec.push_back(*cin_iter++);
    }

    sort(vec.begin(), vec.end());
    ostream_iterator<int> cout_iter(cout, " ");
    unique_copy(vec.begin(), vec.end(), cout_iter);

    cout << endl;
    system("pause");

    return 0;
}