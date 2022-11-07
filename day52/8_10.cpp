#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main(int argc, char *argv[]) {
  std::ifstream in(argv[1]);
  if (!in) {
    std::cerr << "没有输入文件" << std::endl;
  }

  std::string line;
  std::vector<std::string> words;
  while (std::getline(in, line)) {
    words.push_back(line);
  }

  in.close();

  /*std::vector<std::string>::const_iterator it = words.begin();  // 迭代器
  while (it != words.end()) {                         // 遍历 vector
    std::istringstream line_str(*it);
    std::string word;
    while (line_str >> word)  // 通过 istringstream 从 vector 中读取数据
      std::cout << word << '\n';
    ++it;
  }*/

  for (auto &line : words) {
    for (auto &c : line) {
        std::cout << c << std::endl;
    }
  }
  return 0;
}