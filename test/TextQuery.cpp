#include "TextQuery.h"

#include <algorithm>
#include <sstream>

TextQuery::TextQuery(ifstream& input_file) : p_input(new vector<string>) {
  line_type line_number{0};            // 初始化行号
  string line;                         // 用于存储输入的每行文件
  while (getline(input_file, line)) {  // 当文件仍在输入 <algorithm>
    p_input->push_back(line);  // 将文件中的每行存入vector<string>中
    line_number = p_input->size() - 1;  // 行号
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