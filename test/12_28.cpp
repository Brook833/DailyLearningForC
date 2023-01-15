/*************************************************************************
        > File Name: 1.cpp
        > Author: zxc
        > Mail: xiaochuan.zhou@compiler-dev.com
        > Created Time: 2023年01月15日 星期日 13时54分21秒
 ************************************************************************/
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
map<string, set<int>> text_map;

vector<string> input_text;

string clean_str(const string &word) {
  string ret;
  for (auto it = word.begin(); it != word.end(); it++) {
    if (!ispunct(*it)) {
      ret += tolower(*it);
    }
  }
  return ret;
}

void store_intput(ifstream &file) {
  string line;
  string word;
  int line_number = 0;
  while (getline(file, line)) {
    input_text.push_back(line);
    istringstream is(line);
    while (is >> word) {
      string ret = clean_str(word);
      auto word_line = text_map[ret];
      text_map[ret].insert(line_number);
    }
    line_number++;
  }
}

void query_and_print(const string &str, vector<string> &input) {
  auto it = text_map.find(str);
  if (it == text_map.end()) {
    cout << str << "在文本中出现0次" << endl;
  } else {
    cout << str << "在文本中出现" << it->second.size()
         << "次, 分别在: " << endl;
    for (auto c : it->second) {
      cout << "第" << c + 1 << "行"
           << ": " << input_text[c] << endl;
    }
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {  // 未传入查询文件。
    cout << "!!!!!!!" << endl
         << "error" << endl
         << "请正确传入查询文件" << endl;
    return 0;
  }
  string str;
  cin >> str;
  ifstream file(argv[1]);

  store_intput(file);
  query_and_print(str, input_text);

  return 0;
}
