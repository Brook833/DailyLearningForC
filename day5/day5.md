2022.9.13
复习C++primer 2.5处理类型

## 处理类型
### 类型别名
typedef double wages; //wages是double的别名。

新标准规定了一种新的方法，使用别名声明来定义类型的别名

using SI = Sales_item;  //SI是Sales_item的同义词

### 指针，常量和类型别名
如果某个类型别名指代的是复合类型或常量，那么把他用到声明语句里就会产生意想不到的后果。

typedef char *pstring;

const pstring cstr = 0;//cstr是指向char的常量指针

const pstring *ps; //ps是一个指针，它的对象是指向char的常量指针。

遇到一条使用了类型别名的声明语句是，人们往往会错误的尝试把类型别名替换成它本来的样子，以理解该语句的含义；

const char *cstr = 0;//是对const pstring cstr的错误理解。

前者是指向了char的常量指针（指针本身不能改变），后者是指向了const char 的指针。（不能通过该指针改变对象的值)。

### auto 类型说明符
C++11新标准引入了auto类型说明符，可以让编译器去替我们分析表达式所属的类型。显然，auto定义的变量必须有初始值。

auto item = val1 + val2;

### 复合类型，常量和auto
编译器推断出来的auto类型有时候和初始值的类型并不完全一样，编译i去会适当地改变结果类型使其更符合初始化规则。

引用被用作初始值时，真正参与初始化的其实是引用对象的值，此时编译器以引用对象的类型作为auto。

auto会忽略掉顶层const，底层const会被保留下来。

const int ci = i; &cr = ci;

auto b = ci; //b是一个int，顶层const被忽略掉了。

auto c = cr; //c是一个int。

auto d = &i; //d是一个int指针。

auto e = &ci; //e是一个指向整数常量的指针。(底层const)

如果希望推断出的auto类型是一个顶层const，需要使用const auto

### decltype类型指示符
C++11新标准引入了第二种类型说明符decltype，它的作用是返回操作数的数据类型。在此过程中，编译器分析表达式并得到它的类型，却并不实际计算表达式的值。

decltype(f()) sum = x; //sum的类型就是函数f的返回类型。

编译器并不实际调用函数f，而是使用当调用发生时的f的返回值类型作为sum的类型。

decltype可以返回顶层const和引用。

const int ci = 0, &cj = ci;

decltype(ci) x = 0; //x的类型是const int;

decltype(cj) y = x; //y的类型是const int&;

decltype(cj) z; //错误，z的类型是const int&,即引用，必须初始化。

### decltype和引用
int i = 42, *p = &u, &r = i;

decltype(r + 0) b; //加法的结果是int,因此b是一个未经初始化的int.

decltype(*p) c; //错误，c是int&,必须初始化。

decltype(r) 的结果是引用类型，如果想让结果类型是r所指的类型，可以把r作为表达式的一部分，如r+0。

如果表达式的内容是解引用操作,则decltype将得到引用类型，正如我们所熟悉的那样，解引用指针可以得到指针所指的对象，还可以给这个对象赋值，因此decltype(*p)的结果类型就是int&,而非int。

对于decltype所用的表达式来说，如果变量名加上了一对括号（结果类型永远是引用），则得到的类型与不加括号时会有不同。

decltype((i)) d; //错误，d是int&，必须初始化。

decltype(i) e; //e是一个未经初始化的int。