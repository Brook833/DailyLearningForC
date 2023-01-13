#include "TextQuery.h"

#include <iostream>

void runQuery(ifstream & file) {
    TextQuery tq(file);
    while (true) {
        cout << "输入要查找的单词，或输入 q 退出";
        string s;
        if (!(cin >> s) || s == "q") {
            break;
        }
        print_query_result(cout, tq.query(s)) << endl;
    }
}

int main() {
    ifstream file("1.txt");
    runQuery(file);

    return 0;
}