#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 如果 ctr 的值大于 1，返回 word 的复数形式
string make_plural(size_t ctr, const string &word, const string &ending) {
    return (ctr > 1) ? word + ending : word;
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
    sort(words.begin(), words.end());  // words排列成字典序
    (words.begin(), words.end(), [](const string &a, const string &b){ return a.size() < b.size(); });  //按长度排序，相同长度维持字典序
    auto wc = stable_partition(words.begin(), words.end(), [sz](const string &a) { return a.size() >= sz; });
    auto count = wc - words.begin();
    cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer"  << endl;
    for_each(words.begin(), wc, [](const string &s){cout << s << " "; });

    cout << endl;
}

int main() {
 std::vector<std::string> svec = {"the", "quick", "red", "fox", "jumps",
                                     "over", "the", "slow", "red", "turtle"};
    // 按字典序打印 svec 中长度不小于 4 的单词
    biggies(svec, 4);

    system("pause");
    return 0;
}