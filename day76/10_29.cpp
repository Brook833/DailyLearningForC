#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

int main () {
    ifstream ifs("1.txt");
    istream_iterator<string> it(ifs), eof;
    vector<string> s(it, eof);

    ostream_iterator<string> cout_iter(cout, " ");
    copy(s.begin(), s.end(), cout_iter);

    cout << endl;

    system("pause");
    return 0;
}