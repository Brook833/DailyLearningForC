#ifndef TEXTQUERY
#define TEXTQUERY

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

using namespace std;

class QueryResult;
class TextQuery {
 public:
  using LineNo = vector<string>::size_type;
  TextQuery(ifstream &infile);  // 保存文件并建立查询map
  QueryResult query(const string &) const;

 private:
  static string cleanup_str(const string &);
  shared_ptr<vector<string>> input;
  map<string, shared_ptr<set<LineNo>>> query_map;
};

class QueryResult {
 public:
  friend ostream &print_result(ostream &, const QueryResult &);

 public:
  QueryResult(const string &s, shared_ptr<set<TextQuery::LineNo>> set,
              shared_ptr<vector<string>> v)
      : word(s), query_lines(set), input(v) {}

 private:
  string word;                                     // 查询的字符串
  shared_ptr<set<TextQuery::LineNo>> query_lines;  // 查询的字符串对应的行号
  shared_ptr<vector<string>> input;                // 输入
};
#endif  // TEXTQUERY