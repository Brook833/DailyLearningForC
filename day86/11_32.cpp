#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
  system("chcp 65001");

  multimap<string, string> authors{
      {"alan", "DMA"}, {"pezy", "LeetCode"}, {"alan", "CLRS"},
      {"wang", "FTP"}, {"pezy", "CP5"},      {"wang", "CPP-Concurrency"}};
  map<string, set<string>> authors_sort;

  for (auto &author : authors) {
    authors_sort[author.first].insert(author.second);
  }

  for (auto author : authors_sort) {
    cout << author.first << ": ";
    for(auto c : author.second) {
        cout << c << "  ";
    }
    cout << endl;
  }

  system("pause");
  return 0;
}