2022.11.29



### 可变lambda
默认情况下，对于一个值被拷贝的变量，lambda不会改变其值。如果我们希望能改变一个被捕获不限量的值，就必须在参数列表首加上关键字mutable。因此，可变lambda能省略参数列表:

```c++
void fcn3() {
    size_t v1 = 42;  // 局部变量
    // f可以改变它所捕获的变量的值
    auto f = [v1]()mutable{ return ++v1; };
    v1 = 0;
    auto j = f();  // j为43
}
```

==当使用lambda表达式时，若想使用时改变，但是不改变其本体，就可以声明为mutable==
一个引用捕获的变量是否(如往常一样)可以修改依赖于此引用指向的是一个const类型还是一个非const类型:

```c++
void fcn4() {
    size_t v1 = 42;  // 局部变量
    // v1是一个非const变量的引用
    // 可以通过f2中的引用来改变它
    auto f2 = [&v1]{ return ++v1; };
    v1 = 0;
    auto j = f2();  // j为1
}
```

### 指定lambda返回类型
到目前为止，我们所编写的Lambda都只包含单一的return语句。因此，我们还未遇到必须指定返回类型的情况。默认情况下，如果一个lambda体包含return之外的任何语句，则编译器假定此lambda返回void。与其他返回void的函数类似，被推断返回void的lambda不能返回值。

下面给出了一个简单的例子，我们可以使用标准库transform算法和一个lambda来将一个序列中的每个负数替换为其绝对值:

```c++
transform(vi.begin(), vi.end(), vi.begin(), [](int i){ return i < 0 ? -i : i ;});
```

函数transform接受三个迭代器和一个可调用对象。前两个迭代器表示输入序列，第三个迭代器表示目的位置。算法对输入序列中每个元素调用可调用对象，并将结果写到目的位置。如本例所示，目的位置迭代器与表示输入序列开始位置的迭代器可以是相同的。当输入迭代器和目的迭代器相同时，transform将输入序列中每个元素替换为可调用对象操作该元素得到的结果。

在本例中，我们传递给transform一个lambda，它返回其参数的绝对值。lambda体是单一的return语句，返回一个条件表达式的结果。我们无需指定返回类型。但是，如果我们将程序改写为看起来是等价的if语句，就会产生编译错误:

```c++
// 错误，不能推断lambda的返回类型
transform(vi.begin(), vi.end(), vi.begin(), [](int i){ if (i < 0) return -i; else return i;});
```

编译器推断这个版本的lambda返回类型为void，但它返回了一个int值。

当我们需要为一个lambda定义返回类型时，必须使用尾置返回类型:

```c++
transform(vi.begin(), vi.end(), vi.begin(), [](int i)->int{ if (i < 0) return -i; else return i; });
```

在此例中，传递给transform的第四个参数是一个lambda，它的捕获列表是空的，接受单一int参数，返回一个int值。它的函数体是一个返回其参数的绝对值的if语句。

## 10.3.4 参数绑定
==对于那种只在一两个地方使用的简单操作，lambda表达式是最有用的。如果我们需要在很多地方使用相同的操作，通常应该定义一个函数，而不是多次编写相同的lambda表达式.类似的，如果一个操作需要很多语句才能完成，通常使用函数更好。==

如果lambda的捕获列表为空，通常可以用函数来代替它。如前面章节所示，既可以使用一个lambda，也可以用函数isShorter来实现将vector中的单词按长度排序。类似的，对于打印vector内容的lambda，编写一个函数来替换它也是很容易的事情，这个函数只需要接受一个string并在标准输出上打印它即可。

但是对于捕获局部变量的lambda，用函数来替换它就不是那么容易了。例如，我们用在find_if调用中的lambda比较一个string和一个给定大小。我们可以很容易的编写一个完成同样工作的函数:

```c++
bool check_size(const string &s, string::size_type sz) {
    return s.size() >= sz;
}
```

但是我们不能用这个函数作为find_if的一个参数。如前文所示，find_if接受一个一元谓词，因此传递给find_if的可调用对象必须接受一个单一参数。biggies传递给find_if的lambda使用捕获列表来保存sz。为了用check_size来代替此lambda，必须解决如何向sz形参传递一个参数的问题。

### 标准bind函数
我们可以解决向check_size传递一个长度参数的问题，方法是使用一个新的名为bind的标准库函数，它定义在头文件functional中。可以将bind函数看做一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来"适应"原对象的参数列表。

调用bind的一般形式为:

```c++
auto newCallable = bind(callable, arg_list);
```

其中，newCallable本身是一个可调用对象，arg_list是一个逗号分隔的参数列表，对应该定的callable的参数。即，当我们调用newCallable时，newCallable会调用callable，并传递给他arg_list参数。

arg_list中的参数可能包含形如_n的名字，其中n是一个整数。这些参数是"占位符",表示newCallable的参数，它们占据了传递给newCallable的参数的"位置"。数值n表示生成的可调用对象中参数的位置:_1为newCallable的第一个参数，_2为第二个参数，以此类推。

### 绑定check_size的sz参数
作为一个简单的例子，我们将使用bind生成一个调用check_size的对象，如下所示，他用一个定值作为其大小参数来调用check_size:

```c++
// check6是一个可调用对象，接受一个string类型的参数
// 并用此string和值6来调用check_size
auto check6 = bind(check_size, _1, 6);
```

此bind调用只有一个占位符，表示check6只接受单一参数。占位符出现在arg_list的第一个位置，表示check6的醋擦不是个月对于兔八哥check_size的第一个参数。此参数是一个const string&。因此，调用check6必须传递给它一个string类型的参数，check6会将此参数传递给check_size。

```c++
string s = "hello";
bool b1 = check6(s);  // check6(s)会调用check_size(s, 6)
```

使用bind，我们可以将原来基于lambda的find_if调用:

```c++
auto wc = find_if(words.begin(), words.end(), [sz](const string &a));
```

替换为如下版本:

```c++
auto wc = find_if(words.begin(), words.end(), bind(check_size, _1, sz));
```

此bind生成一个可调用对象，将check_size的第二个参数绑定到sz的值。当find_if对words中的string调用这个对象时，这些对象会调用check_size，将给定的string和sz传递给它。因此，find_if可以有效的对输入序列中每个string调用check_size，实现string的大小与sz的比较。

### 使用placeholders名字
名字_n都定义在一个名为placeholders的命名空间中，而这个命名空间本身定义在std命名空间。为了使用这些名字，两个命名空间都要写上。与我们的其他例子类似，对bind的调用代码假定之前已经恰当的使用了using生命。例如，_1对应的using声明为：

```c++
using std::placeholders::_1;
```

此声明说明我们要使用的名字_1定义在命名空间placeholders中，而此命名空间又定义在std中。

对于每个占位符名字，我们都必须提供一个单独的using声明。编写这样的声明很烦人，也很容易出错。可以使用另外一种不同形式的using语句，而不是分别声明每个占位符，如下所示:

```c++
using namespace namespace_name;
```

这种形式说明希望所有来自namespace_name的名字都可以在我们的程序中直接使用。例如:

```c++
using namespace std::placeholders;
```

使得由placeholders定义的所有名字都可用。与bind函数一样，placeholders命名空间也定义在functiona1头文件中。

### bind的参数
如前文所述，我们可以用bind修正参数的值。更一般的，可以用bind绑定给定可调用对象中的参数或重新安排其顺序。例如，假定f是一个可调用对象，它由5个参数,则下面对bind的调用:

```c++
// g是一个有两个参数的可调用对象
auto g = bind(f, a, b, _2, c, _1);
```

生成一个新的可调用对象，它有两个参数，分别用占位符_2和_1表示。这个新的可调用对象将他自己的参数作为第三个和第五个参数传递给f。f的第一个、第二个和第四个参数分别被绑定到给定的值a,b,c上。

传递给g的参数按位置绑定到占位符。即，第一个参数绑定到_1，第二个参数绑定到_2。因此，当我们调用g时，其第一个参数被传递给f作为最后一个参数，第二个参数被传递给f作为第三个参数。实际上，这个bind调用将会:

```c++
g(_1, _2);
```

映射为:

```c++
f(a, b, _2, c, _1);
```

### 用bind重排参数顺序
下面使用bind重排参数是顺序的一个具体例子，我们可以用bind颠倒isShorter的含义:

```c++
// 按单词由短至长排序
sort(words.begin(), words.end(), isShorter);
// 按单词由长至短排序
sort(words.begin(), words.end(), bind(isShorter, _2, _1));
```

### 绑定引用参数
默认情况下，bind的那些不是占位符的参数被拷贝到bind返回的可调用对象中。但是，与lambda类似，有时对有些绑定的参数我们希望以引用方式传递，或是要绑定参数的类型无法拷贝。

例如，为了替换一个引用方式捕获ostream的lambda:

```c++
// os是一个局部变量，引用一个输出流
// c是一个局部变量，类型为char
for_each(words.begin(), words.end(), [&os, c](const string &s){ os << s << c; });
```

可以很容易地编写一个函数，完成相同的工作:

```c++
ostream &print(ostream &os, const string &s, char c) {
    return os << s << c;
}
```

但是不能直接用bind来代替对os的捕获:

```c++
// 错误;不能拷贝os
for_each(words.begin(), words.end(), bind(print, os, _1, ' '));
```

原因在于bind拷贝其参数，而我们不能拷贝一个ostream。如果我们希望传递给bind一个对象而又不拷贝它，就必须使用标准库ref函数:

```c++
for_each(words.begin(), words.end(), bind(print, ref(os), _1, ' '));
```

函数ref返回一个对象，包含给定的引用，此对象是可以拷贝的。标准库中还有一个cref函数，生成一个保存const引用的类。与bind一样，函数ref和cref也定义在头文件functional中。

### 12.1.5 unique_ptr
一个unique_ptr"拥有"它所指向的对象。与shared_ptr不同，某个时刻只能有一个unique_ptr指向一个给定对象。当unique_ptr被销毁时，它所指向的对象也被销毁。表12.4列出了unique_ptr特有的操作。与shared_ptr相同的操作列在表12.1中。

与shared_ptr不同，没有类似make_shared的标准库函数返回一个unique_Ptr。当我们定义一个unique_ptr时，需要将其绑定到一个new返回的指针上。类似shared_ptr，初始化unique_ptr必须采用直接初始化形式:

```c++
unique_ptr<double> p1;  // 可以指向一个double的unique_ptr
unique_ptr<int> p2 (new int(42));  // p2只想一个值为42的int
```

由于一个unique_ptr拥有它指向的对象，因此unique_ptr不支持普通的拷贝或赋值操作:

```c++
unique_ptr<string> p1(new string("Stegosaurus"));
unique_ptr<string> p2(p1);  // 错误:unique_ptr不支持拷贝
unique_ptr<string> p3;
p3 = p2;  // 错误:unique_ptr不支持赋值
```

| 表12.4:unique_ptr操作 |  |
|:- |:- |
| unique_ptr<T> u1 | 空unique_ptr，可以指向类型为T的对象。u1会使用delete来释放它的指针 |
| unique_ptr<T, D> u2 | u2会使用一个类型为D的可调用对象来释放它的指针 |
| unique_ptr<T, D> u(d) | 空unique_ptr，指向类型为T的对象，用类型为D的对象d代替delete |
| u = nullptr | 释放u指向的对象，将u置为空 |
| u.release() | u放弃对指针的控制权，返回指针，并将u置为空 |
| u.reset() | 释放u指向的对象 |
| u.reset(q) | 如果提供了内置指针q，令u指向这个对象；否则将u置为空 |
| u.reset(nullptr) |  |

虽然我们不能拷贝或赋值unique_ptr，但可以通过调用release或reset将指针的所有权从一个(非const)unique_ptr转移给另一个unique:

```c++
unique_ptr<string> p2(p1.release());  // release将p1置为空,将所有权从p1(指向string Stegosaurus)转移给p2
unique_ptr<string> p3(new string("Trex"));
p2.reset(p3.release);  //将所有权从p3转移给p2，reset释放了p2原来指向的内存
```

release成员返回unique_ptr当前保存的指针并将其置为空。因此，p2被初始化为p1原来保存的指针，而p1被置为空。

reset成员接受一个可选的指针参数，令unique_ptr重新指向给定的指针。如果unique_ptr不为空，它原来指向的对象被释放。因此，对p2调用reset释放了用"Stegosaurus"初始化string所使用的内存，将p3对指针的所有权转移给p2,并将p3置为空。

调用release会切断unique_ptr和它原来管理的对象间的关系。release返回的指针通常被用来初始化另一个智能指针或给另一个智能指针赋值。在本例中，管理内存的责任简单的从一个智能指针转移给另一个。但是，如果我们不用另一个智能指针来保存release返回的指针，我们的程序就要负责资源的释放:

```c++
p2.release();  // 错误，p2不会释放内存，而且我们丢失了指针
auto p = p2.release();  // 正确，但我们必须记得delete(p);
```

#### 传递unique_ptr参数和返回unique_ptr
不能拷贝unique_ptr的规则有一个例外:我们可以拷贝或赋值一个将要被销毁的unique_ptr。最常见的例子是从函数返回一个unique_ptr:

```c++
unique_ptr<int> clone(int p) {
    return unique_ptr<int> (new int(p));  // 正确，从int*创建一个unique_ptr<int>
}
```

还可以返回一个局部对象的拷贝:

```c++
unique_ptr<int> clone(int p) {
    unique_ptr<int> ret(new int(p));
    return ret;
}
```

对与两段代码，编译器都知道要返回的对象即将被销毁。在此情况下，编译器执行一种特殊的"拷贝"，我们将在13.6.2节中介绍它。

==向后兼容:auto_ptr
标准库的较早版本包含了一个名为auto_ptr的类，它具有unique_ptr的部分特性，但不是全部。特别是，我们不能在容器中保存auto_ptr,也不能从函数中返回auto_ptr。
虽然auto_ptr仍是标准库的一部分，但编写程序时应该使用unique_ptr。==

#### 向unique_ptr传递删除器
类似shared_ptr，unique_ptr默认情况下用delete释放它指向的对象。与shared_ptr一眼，我们可以重载一个unique_ptr中默认的删除器。但是，unique_ptr管理删除器的方式与shared_ptr不同，其原因我们将在16.1.6节中介绍。

重载一个unique_ptr中的删除器会影响到unique_ptr类型以及如何构造(或reset)该类型的对象。与重载操作关联容器的比较操作类似，我们必须在尖括号中unique_ptr指向类型之后提供删除器类型。在创建或reset一个这种unique_ptr类型的对象时，必须提供一个指定类型的可调用对象(删除器):

```c++
// p指向一个类型为objT的对象，并使用一个类型为detT的对象释放objT对象
// 它会调用一个名为fcn的delT类型对象
unique_ptr<objT, delT>p (new objT, fcn);
```

作为一个更具体的例子，我们将重写连接程序，用unique_ptr代替shared_ptr,如下所示:

```c++
void f(destination &d) {
    connection c = connect(&d);  // 打开连接
    unique_ptr<connectionr, decltype(end_connection) *> p(&c, end_connection);  // 当p被销毁时，连接将会关闭
    // 使用连接
    // 当f退出时(即使时由于异常而退出)，connection会被正确关闭
}
```

在本例中我们使用decltype来之名函数指针类型。由于decltype返回一个函数类型，所以我们必须添加一个*来指出我们正在使用该类型的一个指针。