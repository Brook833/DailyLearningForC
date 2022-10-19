2022.10.15
学习C++primer  6.4.1重载与作用域


### 重载和const形参
顶层const，不影响传入函数的对象。一个拥有顶层const的形参无法和另一个没有顶层const的形参区分开来。

另一方面，如果形参是某种类型的指针或引用，则通过区分其指向的是常量对象还是非常量对象可以实现重载，此时的const是底层的。

编译器可以通过实参是否是常量来推断应该调用哪个函数。因为const不能转换成其他类型，所以我们只能把const对象传递给const形参。

当我们传递一个非常量对象或者指向非常量对象的指针时，编译器会优先选用非常量版本的函数。

### const_cast和重载
const_cast在重载函数的情景中最有用。

```c++
const string &shorterString(const string &s1, const string &s2){
    return s1.size() <= s2.size() ? s1 : s2;
}
```
这个函数的实参和返回类型都是const string的引用。我们可以对两个非常量的string实例调用这个函数，但返回的结果仍然是const string的引用。一次我们需要一种新的shorterString函数，当它的参数不是常量时，得到的结果是一个普通的引用，使用const_cast可以做到这一点。

```c++
string &shorterString(string &s1, string &s2){
    auto &r = shorterString(const_cast<const string&>(s1), const_cast<const string&>(s2));
    return const_cast<string&>(r);
}
```
在这个版本的函数中，首先将它的实参强制转换成对const的引用，然后调用了shorter函数的const版本。const版本返回对const string的引用，这个引用事实绑定在某个初始的非常量实参上。因此，我们可以再将其转换回一个普通的string&，这显然是安全的。

### 调用重载的函数
定义了一组重载函数后，我们需要以合理的实参调用他们。

函数匹配是指一个过程，在这个过程中我们把函数调用与一组重载函数中的某一个关联起来，函数匹配也叫重载确定。

编译器首先将调用的实参与重载集合中每一个函数的形参进行比较，然后根据比较的结果决定到底调用哪个函数。

在很多情况下，程序员很容易判断某次调用是否合法，以及当调用合法时应该调用哪个函数。通常，重载集中的函数区别明显，他们要不然是参数的数量不同，要不就是参数类型毫无关系。

但在另外一些情况下要想选择函数就比较困难了，比如当两个重载函数参数数量相同且参数类型可以相互转换时。

调用重载函数有三种可能的结果：

编译器找到一个与实参最佳匹配的函数，并生成调用该函数的代码。

找不到任何一个函数与调用的实参匹配，此时编译器发出无匹配的错误信息。

有多于一个函数可以匹配，但是每一个都不是明显的最佳选择，此时也将发生错误，成为二义性调用。

## 重载与作用域
对于刚接触C++的程序员来说，不太容易理清作用域和重载的关系。其实，重载对于作用域的一般性质并没有什么改变：如果我们在内层作用域声明名字，它将隐藏外层作用域中声明的同名实体。在不同的作用域中不发重载函数名。
```c++
string read();
void print(const string &);
void print(double); //重载print函数
void fooBar(int ival){
    bool read = false; //新作用域，隐藏了外层的read。
    string s = read(); //错误，read是一个布尔值，而非函数。
    //不好的习惯，通常来说，在局部作用域中声明函数不是一个好的选择。
    void print(int); //新作用域，隐藏了之前的print。
    print("Value:"); //错误，print(const string &)被隐藏掉了。
    print(ival); //正确，当前print(int)可见。
    print(3.14); //正确，调用print(int)。
}
```
在C++语言中，名字查找发生在类型检查之前。