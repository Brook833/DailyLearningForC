2022.10.20
学习C++primer


### 定义一个返回this对象的函数
函数conmbine的设计初衷类似于复合赋值运算符+=，调用该函数的对象代表的是赋值运算符左侧的运算对象，右侧运算对象则通过显式的实参被传入函数：
```c++
Sales_data& Sale_sdata::combine(const Sales_data &rhs) {
    units_sold += rhs.units_sold; //把rhs的成员加到this对象的成员上
    revenue += rhs.revenue;
    return *this; //返回调用该函数的对象
}
```

当我们的交易处理程序调用如下的函数时，
```c++
total.combine(trans); //更新变量total当前的值
```

total的地址被绑定到隐式的this参数上，而rhs绑定到了trans上。因此，当combine执行下面的语句时，
```c++
units_sold += rhs.units_sold; //把rhs成员添加到this对象的成员中
```
效果等同于total.units_sold和trans.unit_sold的和，然后把结果保存到total.units_sold中。

该函数一个值得关注的部分是它的返回类型和返回语句。一般来说，当我们定义的函数类似于某个内置运算符时，应该令该函数的行为尽量模仿这个运算符。内置的赋值运算符把左侧的运算对象当成左值返回，因此为了与它保持一致，combine函数必须返回引用对象。因为此时的左侧运算对象是一个Sales_data的对象，所以返回类型应该是Sales_data&。

如前所述，我们无需使用隐式的this指针访问函数调用者的某个具体成员，而是需要把调用函数的对象当成一个整体来访问：
```c++
return *this;  //返回调用该函数的对象。
```

其中retrun语句解引用this指针以获得执行该函数的对象，换句话说，上面的这个调用返回total的引用。

### 定义类相关的非成员函数
类的作者常常需要定义一些辅助函数，比如add,read和print等。尽管这些函数定义的操作从概念上来说属于类的接口的组成部分，但他们实际不属于类本身。

我们定义非成员函数的方式与定义其他函数一样，通常把函数的生命和定义分离开来。如果函数在概念上属于类但是不定义在类中，则它一般应与类声明在同一个头文件内。在这种方式下，用户使用接口的任何部分都只需要引入一个文件。

一般来说，如果非成员函数是类接口的组成部分，则这些函数的声明应该与类在同一个头文件内

### 定义read和print函数
```c++
//输入的交易信息包括ISBN、售出总数和售出价格
istream &read(istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream &print(ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "  << item.revenue << " " << item.avg_price();
    return os;
}
```
read函数从给定流中将数据读到给定的对象里，print函数则负责将给定对象的内容打印到给定的流中。

除此之外，关于上面的函数还有两点是非常重要的。第一点，read和print分别接受一个各自IO类型的引用作为其参数，这是因为IO类属于不能被拷贝的类型，因此我们只能通过引用来传递他们。而且，因为读取和写入的操作会改变流的内容，所以两个函数接受的都是普通引用，而非对常量的引用。

第二点，print函数不负责换行。一般来说，执行输出任务的函数应该尽量较少对格式的控制，这样可以确保由用户代码来决定是否换行。

### 定义add函数
add函数接收两个Sales_data对象作为其参数，返回值是一个新的Sales_data,用于表示前两个对象的和:
```c++
Salse_data add(const Salse_data &data &lhs, const Sales_data &rhs){
    Sales_data sum = lhs;  //把lhs的数据成员拷贝给sum
    sum.combine(rhs);  //把rhs的数据成员加到sum当中
    return sum;
}
```

在函数体中，我们定义了一个新的Sales_data对象并将其命名为sum。sum将用于存放两笔交易的和，我们用lhs的副本来初始化sum。默认情况下，拷贝类的对象其实拷贝的是对象的数据成员。在拷贝完成之后，sum的bookNo、units_sold和revenue将和lhs一致。接下来我们调用combine函数，将rhs的units_sold和revenue添加给sum，最后，函数返回sum的副本。