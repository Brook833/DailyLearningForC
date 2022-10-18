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
正如useBigger的声明语句所示，直接使用函数指针类型显得冗长而繁琐。类型别名和decltype能让我们简化使用了函数指针的代码：
```c++
typedef decltype(lengthCompare) Func2; //Func2是函数类型
typedef decltype(lengthCompare) *FuncP2; //FuncP2是指向函数的指针
```

### 返回指向函数的指针
和数组类似，虽然不能返回一个函数，但是能返回指向函数类型的指针。然而，我们必须把返回类型写成指针形式，编译器不会自动地将函数返回类型当成对应的指针类型处理。要想声明一个返回函数指针的函数，最简单的办法是使用类型别名：
```c++
using F = int(int*, int); //F是函数类型，不是指针
using PF = int(*)(int*, int);  //PF是指针类型
```
其中我们使用类型别名将F定义成函数类型，将PF定义成指向函数类型的指针。必须时刻注意的是，和函数类型的形参不一样，返回类型不会自动地转换成指针。我们必须显示的将返回类型指定为指针：
```c++
PF f1(int); //正确，PF是指向函数的指针，f1返回指向函数的指针
F f1(int);  //错误，F是函数类型，f1不能返回一个函数
F *f1(int); //正确，显式的指定返回类型是指向函数的指针
```
### 将auto和decltype用于函数指针类型
如果我们明确知道返回的函数是哪一个，就能使用decltype简化书写函数指针返回类型的过程。例如假定有两个函数，它们的返回类型都是string::size_type，并且各有两个const_string&类型的形参，此时我们可以编写第三个函数，它接受一个string类型的参数，返回一个指针，该指针指向前两个函数中的一个。
```c++
string::size_type sumLength(const string&, const string&);
string::size_type largerLength(const string&, const string&);
//根据其形参的取值，getFunc函数返回指向sumLength或者largerLength的指针
decltype(sumLength) *getFybc(const string &);
```

声明getFunc唯一需要注意的地方是，牢记当我们将decltype作用于某个函数时，它返回函数类型而非指针类型。因此我们需要显式的加上*以表明我们需要返回指针，而非函数本身。

int a(int , int);
vector<detype(a) *> p; 