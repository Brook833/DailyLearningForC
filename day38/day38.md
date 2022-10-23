2022.10.23
学习C++primer 7.2.0访问控制与封装


### 访问控制与封装
到目前位置，我们已经为类定义了接口，但并没有任何机制强制用户使用这些接口。我们的类还没有封装，也就是说，用户可以直达Sales_data对象的内部并且控制它的具体实现细节。在C++语言中，我们使用访问说明符加强类的封装性:

定义在public说明符之后的成员在整个成勋内可被访问,public成员定义类的接口。

定义在private说明符之后的成员可以被类的成员函数访问，但是不能被使用该类的代码访问，private部分封装了(即隐藏了)类的实现细节。

再一次定义Sales_data类，其新形式如下：
```c++
class Sales_data {
public: 
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p):bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(const std::string &s) : bookNMo(s) {}
    Sales_data(std::istream&);
    std::string isbn() const { return bookNo; }
    Sales_data &combine(const Sales_data&);
private:
    double avg_price() const { return units_sold ? revenue/units_sold : 0; }
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
```
作为接口的一部分，构造函数和部分成员函数紧跟在Public说明符之后；而数据成员和作为实现部分的函数则跟在private说明符后面。

一个类可以包含0个或多个访问说明符，而且对于某个访问说明符能出现多少次也没有严格限定。每个访问说明符制定了接下来成员的访问级别，其有效范围知道出现下一个访问说明符或者达到类的结尾处为止。

### 使用class或struc关键字
我们可以使用这两个关键字中的任何一个。唯一的一点区别是，struct和class的默认访问权限不太一样。

类可以在它的第一个访问说明符之前定义成员，对于这种成员的访问权限依赖于类定义的方式。struct默认是public。class默认是private。

封装是指保护类的成员不被随意访问的能力。实现类的接口和实现的分离。

封装有两个优点：

确保用户代码不会无意间破坏封装对象的状态。

被封装的类的具体实现细节可以随时改变，而无需调整用户级别的代码。

