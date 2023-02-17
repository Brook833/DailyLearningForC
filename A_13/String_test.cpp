#include "String.h"
#include <vector>
#include <iostream>

void foo(String x)
{
    std::cout << x.c_str() << std::endl;
}

void bar(const String& x)
{
    std::cout << x.c_str() << std::endl;
}

String baz()
{
    String ret("world");
    return ret;
}

int main()
{
    char text[] = "world";

    String s0;                  // 接受C风格字符串指针参数的构造函数 默认构造函数
    String s1("hello");         // 接受C风格字符串指针参数的构造函数
    String s2(s0);              // 拷贝构造函数
    String s3 = s1;             // 拷贝构造函数
    String s4(text);            // 接受C风格字符串指针参数的构造函数
    s2 = s1;                    // 拷贝赋值运算符

    foo(s1);                    // 拷贝构造函数 hello
    bar(s1);                    // hello
    foo("temporary");           // 接受C风格字符串指针参数的构造函数 temporary
    bar("temporary");           // 接受C风格字符串指针参数的构造函数 temporary
    String s5 = baz();          // 接受C风格字符串指针参数的构造函数

    std::vector<String> svec;
    svec.reserve(8);
    svec.push_back(s0);         // 拷贝构造函数 ""
    svec.push_back(s1);         // 拷贝构造函数 hello
    svec.push_back(s2);         // 拷贝构造函数 hello
    svec.push_back(s3);         // 拷贝构造函数 hello
    svec.push_back(s4);         // 拷贝构造函数 world
    svec.push_back(s5);         // 拷贝构造函数 world
    svec.push_back(baz());      // 接受C风格字符串指针参数的构造函数 拷贝构造函数 world
    svec.push_back("good job"); // 接受C风格字符串指针参数的构造函数 拷贝构造函数 good job

    for (const auto& s : svec) {
        std::cout << s.c_str() << std::endl;
    }
}