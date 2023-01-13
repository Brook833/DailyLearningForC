#ifndef TEXTQUERY_QUERYRESULT_
#define TEXTQUERY_QUERYRESULT_

#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

using namespace std;

class QueryResult;
class TextQuery {
 public:
  using line_type = vector<string>::size_type;
  TextQuery(ifstream &);  // 构造函数，存储单词与行号
  QueryResult query(const string &) const;  // 查询函数
 private:
  map<string, shared_ptr<set<line_type>>>
      store_map;  // 存储字符串与其行号信息的map
  shared_ptr<vector<string>> p_input;  // 输入文件
};

class QueryResult {
  friend ostream &print_query_result(ostream &,
                                     const QueryResult &);  // 打印查询信息
 public:
  QueryResult(const string &s, shared_ptr<set<TextQuery::line_type>> p,
              shared_ptr<vector<string>> f)
      : query_word(s), set_lines(p), p_input(f) {}

 private:
  string query_word;  // 要查询的单词
  shared_ptr<set<TextQuery::line_type>>
      set_lines;  // 指向单词对应行号set的智能指针
  shared_ptr<vector<string>> p_input;  // 输入文件
};

std::ostream &print_query_result(std::ostream &, const QueryResult &);
#endif  // TEXTQUERY_QUERYRESULT_