2022.11.02



### 类的静态成员
有的时候类需要他的一些成员与类本身直接相关，而不是与类的各个对象保持关联。例如，一个银行账户类可能需要一个数据成员来表示当前的基准利率。在此例中，我们希望利率与类关联，而非与类的每个对象关联。从实现效率的角度看，没必要每个对象都存储利率信息。而且更加重要的是，一旦利率浮动，我们希望所有的对象都能使用新值。

### 声明静态成员
我们通过在成员的声明之前加上关键字static使得其与类关联在一起。和其他成员一样，静态成员可以是public的或private的。静态数据成员的类型可以是常量、引用、指针、类类型等等。

举个例子，我们定义一个类，用它表示银行的账户纪录：

```c++
class Account {
public:
    void calaulate() { amount += amount * interestRate; }
    static double rate() { return interestate; }
    static void rate(double);
private:
    std::string owner;
    double amount;
    static double interestRate;
    static double ininRate();
};
```

类的静态成员存在于任何对象之外，对象中不包含任何与静态数据成员有关的数据。因此，每个Account对象将包含两个数据成员:owner和amount。只存在一个interestRate对象而且它被所有Account对象共享。

类似的，静态成员函数也不与任何对象绑定在一起，他们不包含this指针。作为结果，静态成员函数不能声明成const的，而且我们也不能在static函数体内使用this指针。这一限制既适用于this的显式使用，也对调用非静态成员的隐式使用有效。

### 使用类的静态成员
我们使用作用域运算符直接访问静态成员:

```c++
double r;
r = Account::rate();  //使用作用域运算符访问静态成员
```

虽然静态成员不属于类的某个对象，但是我们仍然可以使用类的对象、引用或者指针来访问静态成员：

```c++
Account ac1;
Account *ac2 = &ac1;
//调用静态成员rate的等价形式
r = ac1.rate();  //通过Account的对象或引用
r = ac2->rate(); //通过指向Account对象的指针
```

成员函数不用通过作用域运算符就可以直接使用静态成员：

```c++
class Account {
public:
    void calculate() { amount += amount * interestRate; }
private:
    static double interestRate;
};
```

### 定义静态成员
和其他的成员函数一样，我们既可以在类的内部也可以在类的外部定义静态成员函数。当在类的外部定义静态成员时，不能重复static关键字，该关键字只出现在类内部的声明语句:

```c++
void Account::rate(double newRate) {
    interestRate = newRate;
}
```

Note:

和类的所有成员一样，当我们指向类外部的静态成员时，必须之名成员所属的类名。static关键字则值出现在类内部的声明语句中

因为静态数据成员不属于类的任何一个对象，所以它并不是在创建类的对象时被定义的。这意味着他们不是由类的构造函数初始化的。而且一般来说，我们不能在类的内部初始化静态成员。相反的，必须在类的外部定义和初始化每个静态成员。和其他对象一样，一个静态数据成员只能定义一次。

类似与全局变量，静态数据成员定义在任何函数之外。因此一旦它被定义，就将一致存在于程序的整个生命周期中。

我们定义静态数据成员的方式和在类的外度定义成元函数差不多。我们需要指定对象的类姓名，然后是类名、作用域运算符以及成员自己的名字：

```c++
double Account::interestRate = initRate();
```

这条语句定义了名为intrerstRate的对象，该对象是类Account的静态成员，其类型是double。从类名开始，这条定义语句的剩余部分就都位于类的作用域之内了。因此，我们可以直接使用initRate函数。注意虽然initRate是私有的，我们也能用它初始化interestRate。和其他成员的定义一样，interestRate的定义也可以访问类的私有成员。

Tip:

要想确保对象只定义一次，最好的办法是把静态数据成员的定义与其他非内联函数的定义放在同一个文件中

### 静态成员的类内初始化
通常情况下，类的静态成员不应该在类的内部初始化。然而，我们可以喂静态成员提供const整数类型的类内初始值，不过要求静态成员必须是字面值常亮类型的constexpr。初始值必须是常量表达式，因为这些成员本身就是常量表达式，所以它们能用在所有适合于常量表达式的地方。例如，我们可以用一个初始化了的静态数据成员指定数组成员的维度:

```c++
class Account {
    static double rate() { return interestRate; }
    static void rate(double);
private:
    static constexpr int period = 30; //period是常量表达式
    double daily_tbl[period];
};
```

如果某个静态成员的应用场景仅限于编译器可以替换它的值的情况，则一个初始化的const或constexpr static不需要分别定义。嫌烦，如果我们将它用于值不能替换的场景中，则该成员必须有一条定义语句。

例如，如果period的唯一用途就是定义daily_tbl的维度，则不需要在Account外面专门定义period。此时，如果我们忽略了这条定义，那么对程序非常微小的改动也可能造成编译错误，因为程序找不到该成员的定义语句。举个例子，当需要把Account::period传递给一个接受const int&的函数时，必须定义period。

如果在类的内部提供了一个初始值，则成员的定义不能再制定一个初始值了：

```c++
//一个不带初始值的静态成员的定义
constexpr int Account::period  //初始值在类的内部定义内提供
```

即使一个常量静态数据成员在类内部被初始化了，通常情况下也应该在类的外部定义一下该成员。

### 静态成员能用于某些场景，而普通成员不能
如我们所见，静态成员独立于任何对象。因此，在某些非静态数据成员可能非法的场合，静态成员却可以正常的使用。举个例子，静态数据成员可以是不完全类型。特别的，静态数据成员的类型可以是它所属的类类型。而非静态数据成员受到限制，只能声明成它所属的类或指针：

```c++
class Bar {
public:
    //...
private:
    static Bar mem1;  //正确：静态成员可以是不完全类型
    Bar *mem2;        //正确：指针成员可以是不完全类型
    Bar mem3;         //错误：数据成员必须是完全类型
};
```

静态成员和普通成员的另外一个区别是我们可以使用静态成员作为默认实参:

```c++
class Screen {
public:
    //bkground表示一个在类中稍后定义的静态成员
    Screen& clear(char = bkground);
private:
    static const char bkground;
};
```

非静态数据成员不能作为默认实参，因为它的值本身属于对象的一部分，这么做的结果是无法真正提供一个对象以便从中获取成员的值，最终引发错误。

