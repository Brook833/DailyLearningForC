#include <iostream>

#include "TextQuery.h"

void runQuery(ifstream& file) {
  TextQuery tq(file);
  do {
    cout << "输入要查找的单词，或输入 q 退出";
    string s;
    if (!(cin >> s) || s == "q") {
      break;
    }
    print_query_result(cout, tq.query(s)) << endl;
  } while (true);
}

int main() {
  ifstream file("1.txt");
  runQuery(file);

  return 0;
}