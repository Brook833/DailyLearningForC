#include <iostream>
#include <string>
#include <stdexcept>


using namespace std;
int main() {
    system("chcp 65001");

    int v1, v2;
    int result;
    cin >> v1 >> v2;
    if (v2 == 0) {
        throw runtime_error("除数不能为0");
    }
    result = v1 / v2;
    cout << "被除数:" << v1 << endl;
    cout << "除数:" << v2 << endl;
    cout << "结果:" << result << endl;

    system("pause");
    return 0;
}