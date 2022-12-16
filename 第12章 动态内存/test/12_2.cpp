#include <memory>
#include <vector>
#include <string>

class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;
// 构造函数
    std::string& strBlob();
    std::string& strBlob(std::initializer_list<std::string> il);
// 添加和删除元素
    void push_back(const std::string& t) { data->push_back(t); }
    void push_pop(); 
// 访问元素
    std::string& front();
    std::string& back();

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string& msg);
};