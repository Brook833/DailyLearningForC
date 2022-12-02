#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main (int argc, char** argv) {

    ifstream in(argv[1]);
    ofstream out1(argv[2]);
    ofstream out2(argv[3]);


    istream_iterator<int> in_iter(in), eof;
    vector<int> vec, a, b;
    while (in_iter != eof) {
        vec.push_back(*in_iter++);
    }

    for (auto c : vec) {
        if (c / 2) {
            a.push_back(c);  // 奇数
        } else {
            b.push_back(c);  // 偶数
        }
    }

    ostream_iterator<int> out1_iter(out1, " ");
    copy(a.begin(), a.end(), out1_iter);
    out1.close();

    ostream_iterator<int> out2_iter(out2, "\n");
    copy(b.begin(), b.end(), out2_iter);
    out2.close();

    return 0;
}