#ifndef TEXTQUERY_QUERYRESULT_
#define TEXTQUERY_QUERYRESULT_

#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <memory>

using namespace std;

class QueryReuslt;
class TextQuery {
public:
  using line_type = vector<string>::size_type;
  TextQuery(ifstream &);  // 构造函数，存储单词与行号
  QueryReuslt query(const string &) const;  //查询函数
private:
map<string, shared_ptr<set<line_type>>> store_map;  //存储字符串与其行号信息的map
shared_ptr<vector<string>> file;  // 输入文件
};

class QueryResult {
  friend ostream& print_query_result(ostream &, const QueryResult &);  // 打印查询信息
public:
  QueryResult(string &s, shared_ptr<set<line_type>> p, shared_ptr<vector<string>> f);
private:
  string query_word;
  shared_ptr<set<line_type>> store_set;
  shared_ptr<vector<string>> 
};

#endif  // TEXTQUERY_QUERYRESULT_