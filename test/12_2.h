#ifndef STRBLOB_H_
#define STRBLOB_H_

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
    void pop_back(); 
// 访问元素
    std::string& front();
    const std::string& front() const;
    std::string& back();
    const std::string& back() const;

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string& msg) const;
};

void StrBlob::check(size_type i, const std::string& msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

void StrBlob::pop_back() {
    check(0, "push_pop on empty StrBlob");
    data->pop_back();
}

std::string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();

}
const std::string& StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back() {
    check(0, "back on back StrBlob");
    return data->back();
}

const std::string& StrBlob::back() const {
    check(0, "back on back StrBlob");
    return data->back();
}

#endif  // STRBLOB_H_