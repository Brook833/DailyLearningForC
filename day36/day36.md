2022.10.21
学习C++primer


### 构造函数
每个类都分别定义了它的对象被初始化的方式，类通过一个或几个特殊的成员函数来控制其对象的初始化过程，这些函数叫做构造函数。

构造函数的任务是初始化类对象的数据成员，无论何时只要类的对象被创建，就会执行构造函数。

构造函数的名字和类名相同，和其他函数不一样的是，构造函数没有返回类型：除此之外类似于其他的函数，构造函数也有一个(可能为空的)参数列表和一个(可能为空的)函数体。类可以包含多个构造函数，和其他重载函数差不多，不同的构造函数之间必须在参数数量或参数类型上有所区别。

不同于其他成员函数，构造函数不能被声明成const的。当我们创建类的一个const对象时，知道构造函数完成初始化过程，对象才能真正取得其“常量”属性。因此，构造函数在const对象的构造过程中可以向其写值。

### 合成的默认构造函数
我们的Sales_data类并没有定义任何构造函数，可是之前使用了Sales_data对象的程序仍然可以正确的编译和运行。
```c++
Sales_data total; //保存当前求和结果的变量
Sales_data trans; //保存吓一跳交易数据的变量
```
total 和 trans是如何初始化的？

我们没有为这些对象提供初始值，因此我们知道他们执行了默认初始化。类通过一个特殊的构造函数来控制默认初始化过程，这个函数叫做默认构造函数。默认构造函数无需任何实参。

如我们所见，默认构造函数在很多方面都有其特殊性。其中之一是，如果我们的类没有显示的定义构造函数，那么编译器就会为我们隐式地定义一个默认构造函数。

编译器创建的构造函数又被称为合成的默认构造函数。对于大多数类来说，这个合成的默认构造函数将按照如下规则初始化类的数据成员：

如果存在类内的初始值，用它来初始化成员。

否则，默认初始化该成员。

因为Sales_data为units_sold和revenue提供了初始值，所以合成的某人构造函数将使用这些值来初始化对应的成员；同时，它把bookNo默认初始化成一个空字符串。

### 某些类不能依赖于合成的默认构造函数
合成的默认构造函数只适合非常简单的类，比如现在定义的这个Sales_data版本。对于一个普通的类来说，必须定义它自己的默认构造函数，原因有三：

第一个原因也是最容易理解的一个原因就是编译器只有赞发现类不包含任何构造函数的情况下才会替我们生成一个默认的构造函数。一旦我们定义了一些其他的构造函数，那么除非我们再定义一个默认的构造函数，否则类将没有默认构造函数。这条规则的依据是，如果一个类在某种情况下需要控制对象初始化，那么该类很可能在所有情况下都需要控制。

第二个原因是对于某些类来说，合成的默认构造函数可能执行错误的操作。回忆我们之前介绍过的，如果定义在块内的内置类型或复合类型(比如数组和指针)的对象被默认初始化，则他们的值将是未定义的。该准则同样适用于默认初始化的内置类型成员。因此，含有内置类型或复合类型的类应该在类的内部初始化这些成员，或者再定义一个自己的默认构造函数。否则，用户在创建类的对象时就可能得到未定义的值。如果类包含有内置类型或者复合类型成员，则只有当这些成员全都被赋予了类内初始值时，这个类才适用于使用合成的默认构造函数。

第三个原因是有的编译器不能为某些类合成默认的构造函数。例如，如果类中包含一个其他类类型的成员且这个成员的类型没有默认的构造函数，那么编译器将无法初始化该成员。对于这样的类来说，我们必须自定义默认构造函数，否则该类将没有可能的默认构造函数。

### 定义Sales_data的构造函数
对于Sales_data类来说，我们将使用下面的参数定义4个不同的构造函数。

一个istream&，从中读取一条交易信息。

一个const string&,表示ISBN编号；一个unsigned，表示售出的图书数量；以及一个double，表示图书的售出价格

一个const string&,表示ISBN彪悍；编译器将赋予其他成员默认值。

一个空参数列表(即默认构造函数)，正如刚刚介绍的，既然我们已经定义了其他的构造函数，那么也必须定义一个默认构造函数。

给类添加这些成员之后，将得到：
```c++
struct Sales_data {
    //新增的构造函数
    Sales_data() = default;
    Sales_data(const std::string &s) : book(s) {}
    Sales_data(const std::string &s, unsigned n, double p) : 
               bookNo(s), units_sold(n), revenue(p * n) {}
    Sales_data(std::istream &);
    //之前的代码
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
```

### =default的含义
我们从解释默认构造函数的含义开始：
```c++
Sales_data() = default;
```
首先明确一点：因为该构造函数不接受任何实参，所以它是一个默认构造函数。我们定义这个构造函数的目的仅仅是因为我们既需要其他形式的构造函数，也需要默认的构造函数。我们希望这个函数的作用完全等同于之前使用的默认构造函数。

在C++11中，如果我们需要默认的行为，那么可以通过在参数列表后面加上 =default来要求编译器生成构造函数。其中，=default既可以和声明一起出现在类的内部，也可以作为定义出现在类的外部。和其他函数一样，如果=default在类的内部，则默认构造函数是内联的；如果它在类的外部，则该成员默认情况下不是内联的。

上面的默认构造函数之所以对Sales_data有效，是因为哦我们为内置类型的数据成员提供了初始值，如果编译器不支持类内初始值，那么你的某人构造函数就应该使用构造函数初始值列表来初始化每个成员。

### 构造函数初始值列表
接下来介绍类中定义的另外两个构造函数：
```c++
Sales_data(const std::string &s) : bookNo(s) {}
Salse_data(const std::string &s, unsigned n, double p) : bookNo(s),units_sold(n), revenue(p*n) {} 
```
这两个定义中出现了新的部分，即冒号以及冒号和花括号之间的代码，其中花括号定义了函数体。我们把新出现的部分称为构造函数初始值列表，它负责为新创建的对象的一个或几个数据成员赋初始值。构造函数初始值是成员名字的一个列表，每个名字后面紧跟括号括起来的成员初始值。不同的成员的初始化通过逗号分隔开来。

含有三个参数的构造函数分别使用它的前两个参数初始化成员bookNo和units_sold,revenue的初始值则通过将售出图书总数和每本书单价相乘计算得到。

只有一个string类型参数的构造函数使用这个string对象初始化bookNo,对于units_sold和revenue则没有显式地初始化。当某个数据成员被构造函数初始值列表忽略时，它将与合成默认构造函数相同的方式隐式初始化。在此例中，这样的成员使用类内初始值初始化，因此只接受一个string参数的构造函数等价于
```c++
Sales_data(const std::string &s) : bookNo(s), units_sold(0), revenue(0) {}
```

通常情况下，构造函数使用类内初始值不失为一个好的选择，因为hi要这样的初始值存在，我们就能确保为成员赋予了一个正确的值，不过，如果你的编译器不支持类内初始值，则所有的构造函数都应该显式的初始化每个内置类型的成员。

有一点需要注意，在上面的两个构造函数中函数体都是空的，这是因为这些构造函数的唯一目的就是为数据成员赋初始值，一旦没有其他任务需要执行，函数体也就是为空了。

