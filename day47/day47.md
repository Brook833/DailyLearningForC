2022.11.1



## 隐式的类类型转换
如果构造函数只接受了一个实参，则它实际上定义了转换为此类类型的隐式转换机制，有时我们把这种构造函数称作转换构造函数。

Note:

能通过一个实参调用的构造函数定义了一条从构造函数的参数类型向类类型隐式转换的规则。

在Sales_data类中，接受string的构造函数和接受istream的构造函数分别定义了从这两种类型向Sales_data隐式转换的规则，也就是说，在需要使用Sales_data的地方，我们可以使用string或者istream作为替代：

```c++
string null_book = "9-999-99999-9";
//构造一个临时的Sate_data对象
//该对象的Nuit_sold和revenue等于0，bookMp等级mi;;_book
item.combine(null_book);
```

在这里我们用一个string实参调用了Sales_data的combine成员。该调用是合法的，编译器用给定的string自动创建了一个Sales_data对象。新生成的这个(临时)Sales_data对象被传递给combine。因为combine的参数是一个常量引用，所以我们可以给该参数传递一个临时量。

### 只允许一部类类型转换
编译器只会自动地执行一步类型转换。例如，因为下面的地啊吗隐式的使用了两种转换规则，所以他是错误的：

```c++
//错误，需要用户定义的两种转换:
//(1)把"9-999-99999-9"转换成string
//(2)再把这个临时的string转换成Sales_data
item.combine("9-999-99999-9");
```

如果我们想完成上述调用，可以显式的把字符串转换成string或者Sales_data对象：

```c++
//正确:显示的转换成string，隐式的转换成Sales_data
item.combine(string("9-999-99999-9"));
//正确:隐式的转换成string，显式的转换成Sales_data
item.combine(Sales_data("9-999-99999-9"));
```

### 类类型转换不是总有效
是否需要从string到Sales_data的转换依赖于我们对用户使用该转换的看法。在此例中，这种转换可能是对的。null_book中的string可能表示了一个不存在的ISBN编号。

另一个是从istream到Sales_data的转换：

```c++
//使用Istream构造函数创建一个函数传递给combine。
item.combine(cin);
```

这段代码隐式的把cin转换成Sales_data，这个转换执行了接受一个istream的Sales_data构造函数。该构造函数通过读取标准输入创建了一个(临时的)Sales_data对象，随后将得到的对象传递给combine。

Sales_data对象是个临时量，一旦combine完成我们就不能再访问它了。实际上，我们构建了一个对象，先将它的值加到item中，随后将其丢弃。

### 抑制构造函数定义的隐式转换
在要求隐式转换的程序上下文中，我们可以通过构造函数声明为explicit加以阻止：

```c++
class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, doubple p) : bookNo(s), units_sold(n), revenue(p*n) {}
    explicit Sales_data(const std::string &s) : bookNo(s) {}
    explicit Sales_data(std::istream &);
    ...
};
```

此时，没有任何构造函数能够隐式的创建Sales_data对象，之前的两种用法都无法通过编译。

关键字explicit只对一个实参的构造函数有效。需要多个实参的构造函数不能用于执行隐式转换，所以无需将这些构造函数指定为explicit的。只能在类内声明构造函数时使用explicit关键字，在类外部定义时不应重复:

```c++
//错误，explicit关键字只允许出现在类内的构造函数声明处
explicit Sales_data::Sales_data(istream &is) {
    read(is, *this);
}
```

### explicit构造函数只能用于初始化
发生隐式转换的一种情况是当我们执行拷贝形式的初始化时(使用=)。此时，我们只能使用直接初始化而不能使用explicit构造函数:

```c++
Sales_data item1(null_book); //正确，直接初始化
//错误，不能讲explicit构造函数用于拷贝形式的初始化过程
Sales_data item2 = null_book;
```

Note:

当我们用explicit关键字声明构造函数时，它只能以直接初始化的形式使用。而且，编译器将不会在自动转换过程中使用该构造函数。

### 为转换显式地使用构造函数
尽管编译器不会将explicit的构造函数用于隐式转换过程，但是我们可以使用这样的构造函数显式地强制进行转换:

```c++
//正确:实参是一个显式构造的Sales_data对象
item.combine(Sales_data(null_book));
//正确：static_cast可以使用explicit的构造函数
item.combine(static_cast<Sales_data>(cin));
```

在第一个调用中，我们直接使用Sales_data的构造函数，该调用通过接受string的构造函数创建了一个临时的Sales_data对象。在第二个调用中，我们使用static_cast执行了显式的而非隐式的转换。其中,static_cast使用istream构造函数创建了一个临时的Sales_data对象。

### 标准库中含有显式构造函数的类
我们用过的一些标准库中的类含有单参数的构造函数:

接受一个但参数的const char* 的string构造函数不是explicit的。

接受一个容量参数的vector构造函数是explicit的

## 聚合类
聚合类使得用户可以直接访问其成员，并且具有特殊的初始化语法形式。当一个类满足如下条件时，我们可以说他是聚合的：

所有成员都是public的。

没有定义任何构造函数。

没有类内初始值。

没有基类，也没有virtual函数。

例如，下面的类是一个聚合类。

```c++
strcut Data {
    int ival;
    string s;
};
```

我们可以提供一个花括号括起来的成员初始值列表，并用它初始化聚合类的数据成员:

```c++
//val1.ival = 0; vall.s = string("Anna")
Data vall = { 0, "Anna" };
```

初始值的顺序必须与声明的一致，也就是说，第一个成员的初始值要放在第一个，以此类推。

与初始化数组元素的规则一样，如果初始值列表中的元素个数少于类的成员数量，则靠后的成员被值初始化。初始化列表的元素个数绝对不能超过类的成员数量。

值得注意的是，显式的初始化类的对象的成员存在三个明显的缺点：

要求类的所有成员都是public的。

将正确初始化每个对象的每个成员的重任交给了类的用户(而非类的作者)。因为用户很容易忘掉某个初始值，或者提供一个不恰当的初始值，所以这样的初始化过程冗长乏味且容易出错。

添加或删除一个成员之后，所有的初始化语句都需要更新。

## 字面值常量
之前我们提到过constexpr函数的参数和返回值必须是字面值类型。除了算数类型、引用和指针外，某些类也是字面值类型。和其他类不同，字面值类型的类可能含有constexpr函数成员。这样的成员必须符合constexpr函数的所有要求，它们是隐式const的。

数据成员都是字面值类型的聚合类是字面值常量类。如果一个类不是聚合类，但它符合下述要求，则它也是一个字面值常量类:

数据成员都必须是字面值类型。

类必须至少含有一个constexpr构造函数。

如果一个数据成员含有类内初始值，则内置类型成员的初始值必须是一条常量表达式；或者如果成员属于某种类类型，则初始值必须使用成员自己的constexpr构造函数。

类必须使用析构函数的默认定义，该成员负责销毁类的对象。

### constexpr构造函数
尽管构造函数不能是const的，但是字面值常量类的构造函数可以是constexpr函数。事实上，一个字面值常量类必须至少提供一个ocnstexpr构造函数。

constexpr构造函数可以声明成=default的形式(或者是删除函数的形式)。否则，constexpr构造函数就必须符合构造函数的要求(意味着不能包含返回语句),又符合constexpr的要求(意味着它能拥有唯一可执行语句就是返回语句)。综合这两点可知，constexpr构造函数体一般来说是空的。我们通过前置关键字constexpr就可以声明一个constexpr构造函数了:

```c++
class Debug {
public:
    constexpr Debug(bool b = true):hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i, bool o):hw(h), io(i), other(o) {}
    constexpr bool any() { return hw || io || other; }
    void set_io(bool b) { io == b; }
    void set_hw(bool b) { hw == b; }
    void set_other(bool b) { hw == b; }
private:
    bool hw;     //硬件错误，而非IO错误
    bool io;     //IO错误
    bool other;  //其他错误
};
```

constexpr构造函数必须初始化所有数据成员，初始化或者使用constexpr构造函数，或者是一条常量表达式。

constexpr构造函数哟ing与生成constexpr对象以及constexpr函数的参数返回类型：

```c++
constexpr Debug io_sub(false, true, false); //调试IO
if(io_sub.any())  //等价于if(true)
    cerr<< "print appropriate error messages" << endl;
constexpr Debug prod(false) ;
if(prod.any())   //等价于if(false)
    cerr << "print an error message" << endl;
```
