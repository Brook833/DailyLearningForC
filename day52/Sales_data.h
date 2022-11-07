#ifndef TEST_SALES_DATA_H
#define TEST_SALES_DATA_H

// Definition of Sales_data class and related functions goes here
#include <iostream>
#include <string>

// 头文件不应包含 using 声明
// using namespace std;

class Sales_data {
private:                            // 定义私有数据成员
    std::string bookNo;             // 书籍编号，隐士初始化为空串
    unsigned units_sold = 0;        // 销售量，显示初始化为 0
    double sellingprice = 0.0;      // 原始售价，显示初始化为 0.0
    double saleprice = 0.0;         // 实售价格，显示初始化为 0.0
    double discount = 0.0;          // 折扣，显示初始化为 0.0
public:                             // 定义公有函数成员
    // isbn 函数只有一条语句，返回 bookNo
    std::string isbn() const { return bookNo; }
    // combine 函数用于把两个 ISBN 相同的销售记录合并在一起
    Sales_data& combine(const Sales_data &rhs) {
        units_sold += rhs.units_sold;   // 把 rhs 的成员加到 this 对象的成员上
        saleprice = (rhs.saleprice * rhs.units_sold + saleprice * units_sold)
                    / (rhs.units_sold + units_sold);    // 计算平均实际售价
        if (sellingprice != 0)
            discount = saleprice / sellingprice;    // 计算 this 对象的折扣
        return *this;               // 返回调用该函数的对象
    }
    Sales_data add(const Sales_data &lhs, const Sales_data &rhs);
    std::istream &read(std::istream &is, Sales_data &item);
    std::ostream &print(std::ostream &os, const Sales_data &item);
};

Sales_data Sales_data::add(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

std::istream &Sales_data::read(std::istream &is, Sales_data &item) {
    is >> item.bookNo >> item.units_sold >> item.sellingprice >> item.saleprice;
    if (is && item.sellingprice != 0)
        item.discount = item.saleprice / item.sellingprice;
    else
        item = Sales_data();   // 输入错误，重置输入的数据
    return is;
}

std::ostream &Sales_data::print(std::ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " " << item.sellingprice
       << " " << item.saleprice << " " << item.discount;
    return os;
}

#endif //TEST_SALES_DATA_H