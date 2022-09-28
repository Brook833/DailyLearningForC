#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    system("chcp 65001");
    uint32_t now_number = 1, max_number = 0;
    string now_s, pre_s, most_s;

    while (cin >> now_s && now_s != "Q") {
        if (now_s == pre_s) {
            now_number++;
            if (now_number > max_number) {
                max_number = now_number;
                most_s = now_s;
            }
        } else {
            now_number = 1;
        }
        pre_s = now_s;
    }

    if (max_number > 1) {
        cout << most_s << "出现了" << max_number << "次" << endl;
    } else {
        cout << "均只出现了一次" << endl;
    }

    system("pause");
    return 0;
}
