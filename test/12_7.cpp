#include <iostream>
#include <vector>
#include <memory>

using namespace std;

shared_ptr<vector<int>> creat_v(){
    shared_ptr<vector<int>> vp = make_shared<vector<int>>();
    return vp;
}

void init_v(shared_ptr<vector<int>> vp) {
    int i;
    while (cin >> i) {
        vp->push_back(i);
    }
}

void print_v(shared_ptr<vector<int>> vp) {
    for (auto c : *vp) {
        cout << c << endl;
    }
}

int main () {
    shared_ptr<vector<int>> a = creat_v();
    init_v(a);
    print_v(a);

    system("pause");
    return 0;
}