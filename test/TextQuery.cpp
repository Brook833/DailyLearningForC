#include "TextQuery.h"

#include <algorithm>
#include <cstring>
#include <iterator>
#include <sstream>

TextQuery::TextQuery(ifstream& infile) : input(new vector<string>) {
  LineNo lineno{0};  // 初始化行号为0
  for (string text; getline(infile, text); ++lineno) {
    istringstream line_stream(text);
    for (string word, s; line_stream >> word; word.clear()) {
      string ret;
      for (string::const_iterator it = word.begin(); it != word.end(); ++it) {
        if (!ispunct(*it)) ret += tolower(*it);
        word = ret;
      }
      auto& query_lines = query_map[word];  // 使用引用避免shared_ptr添加计数
      if (!query_lines) {  // 如果query_lines为空，说明word是第一次出现
        query_lines.reset(new set<LineNo>);
      }
      query_lines->insert(lineno);  // 无论是否第一次出现，都将该行号添加进set中
    }
  }
}
QueryResult TextQuery::query(const string& str) const {
  static shared_ptr<set<LineNo>> nodata(new set<LineNo>);
  auto found = query_map.find(str);  // 在map中查找
  if (found == query_map.end()) {
    return QueryResult(str, nodata, input);  // 未查找到
  } else {
    return QueryResult(str, found->second, input);
  }
}

ostream& print_result(ostream& out, const QueryResult& qr) {
  out << qr.word << " occurs " << qr.query_lines->size()
      << (qr.query_lines->size() > 1 ? " times" : " time") << endl;
  for (auto c : *qr.query_lines) {
    out << "(line " << c + 1 << ")" << qr.input->at(c) << endl;
  }
  return out;
}