#ifndef STRBLOB_H_
#define STRBLOB_H_

#include <memory>
#include <vector>
#include <string>

class StrBlobPtr;
class StrBlob {
    friend class StrBlobPtr;
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

    //StrBlobPtr begin() { return StrBlob(*this); }

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

class StrBlobPtr {
public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
// 解引用
    std::string& redef() const;
// 递增curr
    StrBlobPtr& incr();
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t, std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;  // 在数组中的当前位置
};
std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, std::string& msg) const {
    auto ret = wptr.lock();
    if (!ret) {
        throw std::runtime_error("unbound StrBlobPtr");
    }
    if (i > ret->size()) {
        throw std::out_of_range(msg);
    }
    return ret;
}

#endif  // STRBLOB_H_