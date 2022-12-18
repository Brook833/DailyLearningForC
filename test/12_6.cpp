#include <iostream>
#include <vector>
#include <memory>

using namespace std;

vector<int>* creat_v(){
    vector<int>* vp = new vector<int>();
    return vp;
}

void init_v(vector<int>* vp) {
    int i;
    while (cin >> i) {
        vp->push_back(i);
    }
}

void print_v(vector<int>* vp) {
    for (auto c : *vp) {
        cout << c << endl;
    }
    delete vp;
}

int main () {
    vector<int>* a = creat_v();
    init_v(a);
    print_v(a);

    system("pause");
    return 0;
}