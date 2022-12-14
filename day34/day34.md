2022.10.19
学习C++primer


## 类
类的基本思想是数据抽象和封装。

数据抽象是一种依赖于接口和实现分离的编程技术。类的接口包括用户所能执行的操作：类的实现则包括类的数据成员、负责接口实现的函数体以及定义类所需的各种私有函数。

封装实现了类的接口和实现的分离。封装后的类隐藏了它的实现细节，也就是说，类的用户只能使用接口而无法访问实现部分。

类要想实现数据抽象和封装，需要首先定义一个抽象数据类型。在抽象数据类型中，由类的设计者负责考虑类的实现过程：使用该类的程序员则只需要抽象的思考类型做了什么，而无需了解类型的工作细节。

## 定义抽象数据类型
程序员们常把运行其程序的人称作用户。类似的，类的设计者也是为其用户设计并实现一个类的人；显然，类的用户是程序员，而非应用程序的最终使用者。

### 定义成员函数
成员函数的声明必须在类的内部，它的定义既可以在类的内部也可以在类的外部。

尽管所有成员都必须在类的内部声明，但是成员函数体可以定义在类内也可以定义在类外。

### 引入this
当我们调用成员函数时，实际上是在替某个对象调用它。

成员函数通过一个名为this的额外隐式参数类访问调用它的那个对象。当我们调用一个成员函数时，用请求该函数的对象地址初始化this。例如，如果调用
```c++
total.isbn();
```
则编译器负责把total的地址传递给isbn的隐式形参this。

在成员函数内部，我们可以直接使用调用该函数的对象的成员，而无需通过成员访问运算符来做到这一点，因为this所指的正是这个对象。任何对类成员的直接访问都被看做this的隐式引用，也就是说，当isbn使用bookNo时，它隐式的使用this指向的成员，就像我们书写了this->bookNo一样。

对我们来说，this形参时隐式定义的。实际上，任何自定义名为this的参数或变量的行为都是非法的。我们可以在成员函数体内部使用this，因此尽管没有必要，但我们还是能把isbn定义成如下的形式；
```c++
std::string isbn() const { return this->bookNo; }
```
因为this的目的总是指向“这个”对象，所以this是一个常量指针，我们不允许改变this中保存的地址

### 引入const成员函数
isbn函数的另一个关键之处是紧随参数列表之后的const关键字，这里，const的作用是修改隐式this指针的类型。

默认情况下，this的类型是指向类类型非常量版本的常量指针。例如在Sales_data成员函数中，this的类型是Sales_data *const。尽管this是隐式的，但它仍然需要遵循初始化规则，意味着，我们不能把this绑定到一个常量对象上。这一情况也就使得我们不能再一个常量对象上调用普通的成员函数。

如果isbn是一个普通函数而且this是一个普通的指针参数，则我们应该把this声明称const Sales_data *const。毕竟，在isbn的函数体内不会改变this所指的对象，所以把this设这位指向常量的指针有助于提高函数的灵活性。

然而，this是隐式的并且不会出现在参数列表中，所以在哪将this声明称指向常量的指针就成为我们必须面对的问题。C++语言的做法是允许把const关键字放在成员函数的参数列表之后，此时，紧跟在参数列表后面的const表示this是一个指向常量的指针。像这样使用const的成员函数被称作常量成员函数。

因为this是指向常量的指针，所以成员函数不能改变调用它的对象的内容。isbn可以读取调用它的对象的数据成员，但是不能写入新值。

常量对象，以及常量对象的引用或指针都只能调用常量成员函数。

### 类作用域和成员函数
类本身就是一个作用域。

类的成员函数定义嵌套在类的作用域之内，因此，isbn中用到的名字bookNo其实就是定义在Sales_data内的数据成员。

值得注意的是，即使bookNo定义在isbn之后,isbn也还是能够使用bookNo。因此，成员函数体可以随意使用类中的其他成员而无需在意这些成员出现的次序。

### 在类的外部定义成员函数
像其他函数一样，当我们在类的外部定义成员函数时，成员函数的定义必须与它的声明匹配。也就是说，返回类型、参数列表和函数名都得与类内部的声明保持一致。如果成员被声明称常量成员函数，那么它的定义也必须在参数列表后明确指定const属性。同时，类外部定义的成员的名字必须包含它所属的类型。
```c++
double Sales_data::avg_price() const {
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}
```
函数名Sales_data::avg_price使用作用域运算符来说明如下的事实：我们定义了一个名为avg_price的函数，并且该函数被声明在类Sales_data的作用域内。
