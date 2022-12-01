2022.12.1



## 10.4.2 iostream迭代器
虽然iostream类型不是容器，但标准库定义了可以用于这些IO类型对象的迭代器。istream_iterator读取输入流，ostream_iterator向一个输出流写数据。这些迭代器蒋它们对应的流当作一个特定类型的元素序列来处理。通过使用流迭代器，我们可以用泛型算法从流对象读取数据以及向其写入数据。

### istream_iterator操作
当创建一个流迭代器时，必须指定迭代器将要读写的对象类型。一个istream_iterator使用>>来读取流。因此，istream_iterator尧都区的类型必须定义了输入运算符。当创建一个istream_iterator时，我们可以将它绑定到一个流。当然，我们还可以默认初始化迭代器，这样就创建了一个可以当做尾后值使用的迭代器。

```c++
istream_iterator<int> int_it(cin);  // 从cin读取int
istream_iterator<int> int_eof;  // 尾后迭代器
ifstream in("afile");
istream_iterator<string> str_it(in);  // 从"afile"读取字符串
```

下面是一个用istream_iterator从标准输入读取数据，存入一个vector的例子:

```c++
istream_iterator<int> in_iter(cin);  // 从cin读取int
istream_iterator<int> eof;  // istream尾后迭代器
while(in != eof) {  // 当有数据可供读取时
// 后置递增运算符读取流，返回迭代器的旧值
// 解引用迭代器,获得从流读取的前一个值
    vec.push_back(*in_iter++);
}
```

此循环从cin读取int值，保存在vec中。在每个循环步中，循环体代码检查in_iter是否等于eof。eof被定义为空的istream_iterator，从而可以当做尾后迭代器来使用。对于一个绑定到流的迭代器，一旦其关联的流遇到文件尾或遇到IO错误，迭代器的值就与尾后迭代器相等。

此程序最困难的部分时传递给push_back的参数，其中用到了解引用运算符和后置递增运算符。该表达式的计算过程与我们之前写过的其他结合解引用和后置递增运算符的表达式一样。后置递增运算符会从流中读取下一个值，向前推进，但返回的是迭代器的旧值。迭代器的旧址包含了从流中读取的前一个值，对迭代器进行解引用就能获得此值。

我们可以将程序重写为如下形式，这体现了istream_iterator更有用的地方:

```c++
istream_iterator<int> in_iter(cin), eof;  // 从cin读取int
vector<int> vec(in_iter, eof);  // 从迭代器范围构造vec
```

本例中我们用一对表示元素范围的迭代器来构造vec。这两个迭代器是istream_iterator，这意味着元素范围是通过从关联的流中读取数据获得的。这个构造函数从cin中读取数据，直至遇到文件尾或者遇到一个不是int的数据位置。从流中读取的数据被用来构造vec。

| **表10.3:istream_iterator操作** |  |
|:- |:- |
| istream_iterator<T> in(is); | in从输入流is读取类型为T的值 |
| istream_iterator<T> end; | 读取值为T的istream_iterator迭代器,表示尾后位置 |
| in1 == in2 | in1和in2必须读取相同类型。乳沟它们都是尾后迭代器，或绑定到相同的输入，则二者相等 |
| in1 != in2 |  |
| *in | 返回从流中读取的值 |
| in->mem | 与(*in).mem含义相同 |
| ++in, in++ | 使用元素类型所定义的>>运算符从输入流读取下一个值。与往常一样，前置版本返回一个指向递增后迭代器的引用，后置版本返回旧值 |

### 使用算法操作流迭代器
由于算法使用迭代器操作来处理数据，而流迭代器又至少支持某些迭代器操作，因此我们至少可以用某些算法来操作流迭代器。我们在10.5.1节会看到如何分辨那些算法可以用于流迭代器。下面是一个例子，我们可以用一对istream_iterator来调用accumulate:

```c++
istream_iterator<int> in(cin), eof;
cout << accumulate(in, eof, 0) << endl;
```

此调用会计算出从标准输入读取的值的和。如果输入为:

```c++
23 109 45 89 6 34 12 90 34 23 56 23 8 89 23
```

则输入为664。

### istream_iterator允许使用懒惰求值
当我们将一个istream_iterator绑定到一个流时，标准库并不保证迭代器立即从流读取数据，具体实现可以推迟从流中读取数据，直到我们使用迭代器时才真正读取。标准库中的实现所保证的是，在我们第一次解引用迭代器之前，从流中读取数据的操作已经完成了。对于大多数程序来说，立即读取和推迟读取没什么差别，但是，如果我们创建了一个ostream_iterator，没有使用就销毁了，或者我们正在从两个不同的对象同步读取同一个流，那么何时读取可能就很重要了。

### ostream_iterator操作
我们可以对任何具有输出运算符(<<运算符)的类型定义ostream_iterator。当创建一个ostream_iterator时，我们可以提供(可选的)第二参数，它是一个字符串，在输出每个元素后都会打印此字符串。此字符串必须是一个C风格字符串(即，一个字符串字面常量或者一个指向以空字符结尾的字符数组的指针)。必须将ostream_iterator绑定到一个指定的流，不允许空的或表示尾后位置的ostream_iterator。

| **表10.4:ostream_iterator操作** |  |
| ostream_iterator<T> out(os); | out将类型为T的值写到输出流os中 |
| ostream_iterator<T> out(os, d); | out将类型为T的值写到输出流os中，每个值后面都输出一个d。d指向一个空字符结尾的字符数组 |
| out = val | 用<<运算符将val写入到out所绑定的ostream中。val的类型必须与out可写的类型兼容。 |
| *out, ++out, out++ | 这些运算符是存在的，但不对out做任何事情。每个运算符都返回out |

我们可以用ostream_iterator来输出值的序列:

```c++
ostream_oterator<int> out_iter(cout, " ");
for (auto e : vec) {
    *out_iter++ = e;  // 赋值语句实际上将元素写入cout
}
cout << endl;
```

此程序将vec中的每个元素写到cout，每个元素后加一个空格。每次向out_iter赋值时，写操作就会被提交。

值的注意的是，当我们向out_iter赋值时，可以忽略解引用和递增运算。即，循环可以重写成下面这个样子:

```c++
for (auto e : vec) {
    out_iter = e;  // 赋值语句将元素写入cout
}
cout << endl;
```

运算符*和++实际上对ostream_iterator对象不做任何事，因此忽略它们对我们的程序没有任何影响。但是，推荐第一种形式。在这种写法中，流迭代器的使用与其他迭代器的使用保持一致。如果像将此循环改为其他迭代器类型，修改起来也非常容器。而且，对于读者来说，此循环的行为也更为清晰。

可以通过调用copy来打印vec中的元素，这比编写循环更为简单:

```c++
copy(vec.begin(),vec.end(), out_iter);
cout << endl;
```

### 使用流迭代器处理类类型
我们可以为任何定义了输入运算符(>>)的类型创建istream_iterator对象。类型的，只要类型有输出运算符(<<)，我们就可以为其定义ostream_iterator。由于Sales_item既有输入运算符也有输出运算符，因此可以使用IO迭代器重写书店程序：

```c++
istream_iterator<Sales_item> item_iter(cin), eof;
ostream_iterator<Sale_item> out_iter(cout, "\n");
// 将第一笔交易记录存在sum中，并读取下一条记录
Sales_item sum = *item_iter++;
while(item_iter != eof) {
    // 如果当前交易记录(存在item_iter中)有着相同的ISBN号
    if(item_iter->isbn() == sum.isbn()) {
        sum += *item_iter++;  // 将其加到sum上并读取下一条记录
    } else {
        out_iter = sum;  // 输出sum当前值
        sum = *item_iter++;  // 读取下一条记录
    }
}
out_iter = sum;  // 记得打印最后一组记录的和
```

此程序使用item_iter从cin读取Sales_item交易记录，并将和写入cout，每个结果后面都跟一个换行符。定义了自己的迭代器后，我们就可以用item_iter读取第一条交易记录，用它的值来初始化sum:

```c++
// 将第一条交易记录保存在sum中，并读取下一条记录
Sales_item sum = *item_iter++;
```

此处，我们对item_item执行后置递增操作，对结果进行解引用操作。这个表达式读取下一条交易记录，并用之前保存在item_iter中的值来初始化sum。

while循环会反复执行，直至在cin上遇到文件尾为止。在while循环体中，我们检查sum与刚刚读入的记录是否对应同一本书。如果两者的ISBN不同，我们将sum赋予out_iter，这将会打印sum的当前值，并接着打印一个换行符。在打印了前一本书的交易金额之和后，我们将最近读入的交易记录的副本赋予sum，并递增迭代器，这将读取下一条交易记录。循环会这样持续下去，直至遇到错误或文件尾。在推出之前，记住要打印输入中最后一本书的交易金额之和。
