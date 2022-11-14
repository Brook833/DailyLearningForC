#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

int main() {
    string word;
    
    /*list<string> l;
    auto iter = l.begin();
    while (cin >> word) {
        iter = l.insert(iter, word);
    }*/

    vector<string> vs {"Hello"};
    auto iter2 = vs.end();
    while (cin >> word) {
        iter2 = vs.insert(iter2, word);
    }

    for (auto &c : vs) {
        cout << c << endl;
    }
    system("pause");
    return 0;
}