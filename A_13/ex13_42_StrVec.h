#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <memory>
#include <initializer_list>

using namespace std;

class StrVec
{
private:
    static allocator<string> alloc;  // 分配元素
    string* elements;                // 指向数组首元素的指针
    string* first_free;              // 指向数组第一个空闲位置的指针
    string* cap;                     // 指向数组尾后位置的指针

public:

    StrVec():elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(initializer_list<string>);
    StrVec(const StrVec&);
    StrVec& operator= (const StrVec&);
    ~StrVec();

    void push_back(const string&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    string* begin() const { return elements; }
    string* end() const { return first_free; }
};


#endif  // STRVEC_H_
