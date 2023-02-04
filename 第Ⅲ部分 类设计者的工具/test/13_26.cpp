#include <memory>
#include <vector>
#include <string>

using namespace std;

class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;
// 构造函数
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
// 拷贝构造函数
   StrBlob(const StrBlob &s) : data(make_shared<vector<string>> (*s.data)) {}
   StrBlob& operator= (const StrBlob &s) {
    auto p = make_shared<vector<string>> (*s.data);
    p = data;
    return *this;
   }

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string& msg) const;
};