#include "TextQuery.h"

#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

TextQuery::TextQuery(ifstream& input_file) : p_input(new vector<string>) {            // 初始化行号
  string line;                         // 用于存储输入的每行文件
  while (getline(input_file, line)) {  // 当文件仍在输入 <algorithm>
    p_input->push_back(line);  // 将文件中的每行存入vector<string>中
    int line_number = p_input->size() - 1;  // 行号
    istringstream is(line);             // <sstream>
    string word;                        // 把一行分成每个单词
    while (is >> word) {
      auto& set_lines =
          store_map[word];  // set_lines为shared_ptr<set<line_type>>
      if (!set_lines) {     // 即该word之前未出现过
        set_lines.reset(new set<line_type>);  // 重新指向新分配的set
      }
      set_lines->insert(line_number);  // 将行号存入保存行号的set中
    }
  }
}

QueryResult TextQuery::query(const string& word) const {
  static shared_ptr<set<line_type>> nodate(new set<line_type>);
  auto it = store_map.find(word);
  if (it == store_map.end()) {
    cout << "nodate" << endl;
    return QueryResult(word, nodate, p_input);
  } else {
    cout << "isdata" << endl;
    return QueryResult(word, it->second, p_input);
  }
}

ostream& print_query_result(ostream& out, const QueryResult& qr) {
   out << qr.query_word << "出现了" << qr.set_lines->size() << "次" << endl;
   for (auto c : *qr.set_lines) {
    out << c << ": //" << *(qr.p_input->begin() + c) << endl;
   }

   for (auto c : *qr.p_input) {
    cout << c << " ";
   }
   return out;
}