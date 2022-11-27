2022.11.26



### 10.3.2 lambda表达式
根据算法接受一元谓词还是二元谓词，我们传递给算法的谓词必须严格接受一个或两个参数。但是，有时我们希望进行的操作需要更多参数，超出了算法对谓词的限制。例如，为上一个节后一个练习所编写的程序中，就必须将大小5硬编码到划分序列的谓词中。如果在编写划分序列的谓词时，可以不必为每个可能的大小都编写一个独立的谓词，显然更有实际价值。

一个相关的例子是，求大于等于一个给定长度的单词有多少。我们还会修改输出，使程序只打印大于等于给定长度的单词。

我们将此函数命名为biggies，其框架如下所示:

```c++
void biggies(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);  // 将words按字典序排序，删除重复单词
    // 按长度排序，长度相同的单词维持字典序
    stable_sort(words.begin(), words.end(), isShorter);
    // 获取一个迭代器，指向第一个size() >= sz 的元素
    // 计算满足size >= sz的元素的数目
    // 打印长度大于等于给定值的单词，每个单词后面接一个空格
}
```

我们的新问题是在vector中寻找第一个大于等于给定长度的元素。一旦找到这个元素，根据其位置，就可以计算出有多少元素的长度大于等于给定值。

我们可以使用标准库find_if算法来查找第一个具有特定大小的元素。类似find，find_if算法接受一对迭代器，表示一个范围。但与find不同的是，find_if的第三个参数是一个谓词。它返回第一个使谓词非0值的元素，如果不存在这样的元素，则返回尾迭代器。

编写一个函数，令其接受一个string和一个长度，并返回一个bool值表示该string的长度是否大于给定长度，是一件很容易的事情。但是，find_if接受一元谓词————我们传递给find_if的任何函数都必须严格接受一个参数，以便能用来自输入序列的一个元素调用它。没有任何办法能传递给它第二个参数来表示长度。为了解决此问题。需要使用另外一些语言特性。

### 介绍lambda
我们可以向一个算法传递任何类别的可调用对象(callable object)。对于一个对象或一个表达式，如果可以对其使用调用运算符，则称它为可调用的。即，如果e是一个可调用的表达式，即我们可以编写代码e(args)，其中args是一个逗号分隔的一个或多个参数的列表。

到目前为止，我们使用过的仅有两种可调用对象是函数和函数指针。还有其他两种可调用对象:重载了函数调用运算符的类以及lambda表达式。

==一个lambda表达式表示一个可调用的代码单元==。我们可以将其理解为一个未命名的内联函数。与任何函数类似，一个lambda具有一个返回类型，一个参数列表和一个函数体。但与函数不同，lambda可能定义在函数内部。一个lambda表达式具有如下形式:

```c++
[capture list](parameter list) -> return type { function body }
```

其中，capture list(捕获列表)是一个lambda所在函数中定义的局部变量的列表(通常为空)；return type、parameter list和function body与任何普通函数一样，分别表示返回类型、参数列表和函数体。但是，与普通函数不同，lambda必须使用尾置返回来指定返回类型。

我们可以忽略参数列表和返回类型，但必须永远包含捕获列表和函数体。

```c++
auto f = []{ return 42; };
```

此例中，我们定义了一个可调用对象f，它不接受参数，返回42。

lambda的调用方式与普通函数的调用方式相同，都是使用调用运算符:

```c++
cout << f() << endl;
```

在lambda中忽略括号和参数列表等价于指定一个空参数列表。在此例中，当调用f时，参数列表是空的。如果忽略返回类型，lambda根据函数体内的代码推断出返回类型。如果函数体只是一个return语句，则返回类型从返回的表达式的类型推断而来。否则，返回类型为void。

**Note: 如果lambda的函数体包含任何单一return语句之外的内容，且未指定任何返回类型，则返回void。**

### 向lambda传递函数
与一个普通函数调用类似，调用一个lambda时给定的实参被用来初始化lambda的形参。通常，实参和形参的类型必须匹配。但与普通函数不同,lambda不能有默认参数。因此，一个lambda调用的实参数目永远与形参数目相等。一旦形参初始化完毕，就可以执行函数体了。

作为一个带参数的lambda的例子，我们可以编写一个与isShorter函数完成相同功能的lambda:

```c++
[](const string &a, const string &b) { return a.size() < b.size(); }
```

空捕获列表证明此lambda不使用它所在函数中的任何局部变量。lambda的参数与isShorter的参数类似，是const string的引用。lambda的函数体也与isShorter类似，比较其两个参数的size(),并根据两者的相对大小返回一个布尔值。

如下所示,可以使用此lambda来调用stable_sort:

```c++
// 按长度排序，长度相同的单词维持字典序
stable_sort(words.begin(), words.end(), [](const string &a, const string &b){return a.size() < b.size(); });
```

当stable_sort需要比较两个元素时，他就会调用给定的lambda表达式。

### 使用捕获列表
我们现在已经准备号解决原来的问题了————编写一个可以传递给find_if的可调用表达式。我们希望这个表达式能将输入序列中每个string的长度与biggies函数中的sz参数的值进行比较。

虽然一个lambda可以出现在一个函数中，使用其局部变量，但他只能使用那些明确知名的变量，一个lambda通过将局部变量包含在其捕获列表中来指出将会使用这些变量。捕获列表指引lambda在其内部包含访问局部变量所需的信息。

在本例中，我们的lambda会捕获sz，并只有单一的string参数。其函数体会将string的大小与捕获的sz的值进行比较:

```c++
[sz](const string &a){ return a.size() >= sz; };
```

lambda以一对[]开始，我们可以在其中提供一个以逗号分隔的名字列表，这些名字都是它所在函数中定义的。

由于此lambda捕获sz，因此lambda的函数体可以使用sz。lambda不捕获words，因此不能访问此变量。如果我们给lambda提供一个空捕获列表，则代码会编译错误:

```c++
// 错误，sz未捕获
[](const string &a){ return a.size() >= sz; };
```

**Note:一个lambda只有在其捕获列表中捕获一个他所在函数中的局部变量，才能在函数体中使用该变量。**

### 调用find_if
使用此lambda，我们就可以查找第一个长度大于等于sz的元素:

```c++
// 获取一个迭代器，指向第一个满足size() >= sz的元素
auto wc = find_if(words.begin(), words.end(), [sz](const string &a){ return a.size() >= sz; });
```

这里对find_if的调用返回一个迭代器，指向第一个长度不小于给定参数sz的元素。如果这样的元素不存在，则返回words.end()的一个拷贝。

我们可以使用find_if返回的迭代器来计算从他开始到words的末尾一共有多少个元素:

```c++
// 计算满足size >= sz的元素的数目
auto count = words.end() - wc;
cout << conut << " " << make_plural(count, "word", "s") << " of length" << sz << " or longer"  << endl;
```

我们的输出语句调用make_plural来输出"word" 或 "words",具体输出哪个取决于大小是否等于1。

### for_each算法
问题的最后一部分是打印words中长度大于等于sz的元素。为了达到这一目的，我们可以使用for_each算法。此算法接受一个可调用对象，并对输入序列中每个元素调用此对象:

```c++
// 打印长度大于等于给定值的单词，每个单词后面接一个空格
for_each(wc, words.end(), [](const string &s){cout << s " "; });
cout << endl;
```

此lambda中的捕获列表为空，但其函数体中还是使用了两个名字:s和cout，前者是他自己的参数。

捕获列表为空，是因为我们只对lambda所在函数中定义的(非static)变量使用捕获列表。一个lambda可以直接使用定义在当前函数之外的名字。在本例中，cout不是定义在biggies中的局部名字，而是定义在头文件iostream中。因此，只要在biggies出现的作用域包含了头文件iostream，我们的lambda就可以使用cout。

**Note:捕获列表只用于局部非static变量，lambda可以直接使用局部static变量和在他函数之外声明的名字。**‘

### 完整的biggies
到目前为止，我们解决了程序所有的细节，下面就是完整的程序:

```c++
void biggies(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);  // 将words按字典序排列，删除重复单词
    stable_sort(words.begin(), words.end(), [](const string &a, const string &b){ return a.size() < b.size(); });  //按长度排序，长度相同的维持字典序
    auto wc = find_if(words.begin(), words.end(),[sz](const string &a){ return a.size() >= sz; });  //获取一个迭代器，指向第一个满足size() >= sz的元素。
    auto count = words.end() - wc;  // 计算满足size() >= sz的元素的数目
    cout << conut << " " << make_plural(count, "word", "s") << " of length" << sz << " or longer"  << endl;
    for_each(wc, words.end(),[](const string &s){cout << s << " "; });
    cout << endl;
}