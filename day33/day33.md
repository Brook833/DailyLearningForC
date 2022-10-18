2022.10.18



## 函数指针
函数指针指向的是函数而非对象。

和其他指针一样，函数指针只想某种特定类型。函数的类型由它的返回类型和形参类型共同决定，与函数名无关。例如

bool lengthCompare(const string &, const string &); //比较两个string对象的长度

该函数的类型是bool (const string &, const string &).

要想声明一个可以指向该函数的指针，只需要用指针替换函数名即可：

bool (*pf)(const string &, const string &);

*pf两端的括号必不可少，如果不写这对括号，则pf是一个返回值未bool指针的函数

### 使用函数指针
当我们把函数名作为一个一个值使用时，该函数自动地转换成指针。例如,按照如下形式我们可以将lengthCompare的地址赋给pf:

pf = lengthCompare;  //pf指向名为lengthCompare的函数。
pf = &lengthCompare; //等价的赋值语句，取地址符是可选的。

此外，我们还能直接使用指向函数的指针调用该函数，无须提前解引用指针：

bool b1 = pf("hello", "goodbye"); //调用lengthCompare函数。

bool b2 = (*pf)("hello", "goodbye"); //一个等价的调用。

bool b3 = lengthCompare("hello", "goodbye"); //另一个等价的调用。

在指向不同函数类型的指针间不存在转换规则。但是和往常一样，我们可以为函数指针赋一个nullptr或值为0的整形常量表达式，表示该指针没有指向任何的函数。

### 重载函数的指针
当我们使用重载函数时，上下文必须清晰地界定到底选用哪个函数。

编译器通过指针类型决定选用哪个函数，指针类型必须与重载中的某一个精确匹配。

### 函数指针形参
和数组类似，虽然不能定义函数类型的形参，但是形参可以是指向函数的指针。此时，形参看起来是函数类型，实际上确实当成指针在使用。
```c++
void useBigger(const string &s1, const string &s2, bool pf(const string &, const string &)); //第三个形参是函数类型，它会自动转换成指向函数的指针。
void useBigger(const string &s1, const string &s2, bool (*pf)(const string &, const string &)); //等价的声明，显式的将形参定义成指向函数的指针。
```
我们可以直接把函数作为实参使用，此时它会自动转换成指针。
```c++
useBigger(s1, s2, lengthCompare); //自动将函数lengthCompare转换成指向该函数的指针
```
