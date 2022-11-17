2011.11.17



### capacity和size
理解capacity和size的区别非常重要。容器的size实质它已经保存的元素的数目；而capacity则是在不分配新的内存空间的前提下它最多可以保存多少元素。

下面的代码展示了size和capacity之间的相互作用：

```c++
vector<int> ivec;
// size应该尾0；capacity的值依赖于具体实现
cout << " ivec: size: " << ivec.size() << "capacity: " << ivec.capacity() << endl;
// 向ivec添加24个元素
for (vector<int>::size_type ix = 0; ix != 24; ix++) {
    ivec.push_back(ix);
}
// size应该为24；capacity应该大于等于24，具体值依赖于标准库实现
cout << " ivec: size: " << ivec.size() << "capacity: " << ivec.capacity() << endl;
```

这段程序得到如下结果:

```c++
ivec: size: 0  capacity: 0
ivec: size: 24  capacity: 32
```

我们知道一个空vector的size为0，显然在我们的标准库实现中一个空vector的capacity也为0.当向vector中添加元素时，我们知道size与添加的元素数目相等。而capacity至少与size意义大，具体会分配多少额外空间视标准库具体实现而定。在我们标准库实现中，每次添加1个元素，共添加24个元素，会使capacity变为32.

现在可以预分配一些额外空间：

```c++
ivec.reserve(50);  // 将capacity至少设定为50，可能会更大
// size应为24；capacity应该大于等于50，具体值依赖于标准库实现
cout << " ivec: size: " << ivec.size() << "capacity: " << ivec.capacity() << endl;
```

程序的输出表明reserve严格按照我们需求的大小分配了新的空间：

```c++
ivec: size: 24  capacity: 50
```

接下来可以用光这些预留空间：

```c++
// 添加元素用光多余容量
while (ivec.size() != ivec.capacity()) {
    ivec.push_back(0);
// capacity应该未改变，size和capacity不相等
}
cout << " ivec: size: " << ivec.size() << "capacity: " << ivec.capacity() << endl;

成熟输出表明此时我们确实用光了预留空间，size和capacity相等:

```c++
ivec: size: 50  capacity: 50
```

由于我们只是用了预留空间，因此没有必须要为vector分配新的空间。实际上，只要没有操作需求超出vector的容量，vector就不能重新分配内存空间。

如果我们现在再添加一个新元素，vector就不得不重新分配空间:

```c++
ivec.push_back(42);  // 再添加一个元素
// size应该为51; capacity应该大于等于51，具体值依赖于标准库实现
cout << " ivec: size: " << ivec.size() << "capacity: " << ivec.capacity() << endl;
```

这段程序输出为:

```c++
ivec: size: 51  capacity: 100
```

这表明vector的实现采用的策略似乎是在每次需要分配新内存空间时将当前容量翻倍。

可以调用shrink_to_fit来要求vector将超出当前大小的多余内存退回给系统:

```c++
ivec.shrink_to_fit();  // 要求归还内存
// size应该未改变；capacity值依赖于具体实现
cout << " ivec: size: " << ivec.size() << "capacity: " << ivec.capacity() << endl;
```

调用shrink_to_fit只是一个请求，标准库并不保证退还内存。

**Note: 每个vector实现都可以选择自己的内存分配策略。但是必须遵守的一条原则是，只有迫不得已时才可以重新分配内存空间**

只有在执行insert操作时size与capacity相等，或者调用resize或reserve时，给定的大小超过当前capacity，vector才可能重新分配内存空间。会分配多少超过给定容量的额外空间，取决于具体实现。

虽然不同的实现可以采用的不同的分配策略，但所有的实现都应遵循一个原则：确保用push_back向vector添加元素的操作有高效率。从技术角度说，就是通过在一个初始为空的vector上调用n次push_back来创建一个n个元素的vector，所花费的时间不能超过n的常数倍。

# 9.5 额外的string操作
出了顺序容器共同的操作之外，string类型还提供了一些额外的操作。这些操作中的大部分要么时提供string类和C风格字符数组之间的相互转换，要么时增加了允许我们用下标代替迭代器的版本。

标准库string类型定义了大量函数，幸运的是，这些函数使用了重复的模式。

## 9.5.1 构造string的其他方法
string类型还支持另外三个构造函数。

| **表9.5: 构造string的其他方法** |  |
|:- |:- |
| n、len2和pos2都是无符号值 |  |
| string s(cp, n) | s是cp指向的数组中前n个字符的拷贝。此数组至少应该包含n个字符 |
| string s(s2, pos2) | s是string s2从下标pos2开始的字符的拷贝。若pos2 > s2.size(),构造函数的行为未定义 |
| string s(s2, pos2, len2) | s是string s2从下标pos2开始len2个字符的拷贝。若pos2>s2.size()，构造函数的行为未定义。不管len2的值是多少，构造函数之多拷贝s2.size() - pos2个字符 |

这些构造函数接受一个string或一个const char*参数。还接受(可选的)制定拷贝多少个字符的参数。当我们传递给他们的是一个string时，还可以给定一个下标来支出从哪里开始拷贝:

```c++
const char *cp = "Hello World!!!";  // 以空字符结束的数组
char noNull[] = {'H', 'i'};  // 不是以空字符结束
stirng s1(cp);  // 拷贝cp中的字符知道遇到空字符; s1 == "Hello World!!!"
string s2(noNull, 2);  // 从noNull拷贝两个字符；s2 == "Hi"
string s3(noNull);  // 未定义，noNull不是以空字符奇数
string s4(cp + 6, 5);  // 从cp[6]开始拷贝5个字符； s4 == "World";
string s5(s1, 6, 5);  // 从s1[6]开始拷贝5个字符； s5 == ”World";
string s6(s1, 6);  // 从s1[6]开始拷贝，直至s1末尾； s6 == "World!!!";
string s7(s1, 6, 20);  // 正确，只拷贝到s1末尾；s7 -- "World!!!";
string s8(s1, 16);  // 抛出一个out_of_range异常
```

通常当我们从一个const char*创建string时，指针指向的数组必须以空字符结尾，拷贝操作遇到空字符时停止。如果我们还传递给构造函数一个计数值，数组就不必以空字符结尾。如果我们未传递计数值且数组也未以空字符结尾，或者给定计数值大于数组大小，则构造函数的行为是未定义的。

当从一个string拷贝字符时，我们可以提供一个可选的开始位置和一个计数值。开始位置必须小于或等于给定的string大小。如果位置大于size，则构造函数抛出一个out_of_range异常。如果我们传递了一个计数值，则从给定位置开始拷贝这么多个字符。不管我们要求拷贝多少字符，标准库最多拷贝到string结尾，不会更多。

### substr操作
substr操作返回一个string，它是原始string的一部分或全部的拷贝。可以传递给substr一个可选的开始位置和计数值:

```c++
string s("hello world");
string s2 = s.substr(0, 5);  // s2 = hello;
string s3 = s.substr(6);  // s3 = world;
string s4 = s.substr(6, 11);  // s4 = world;
string s5 = s.substr(12);  // 抛出一个out_of_range异常
```

如果开始位置超过了string的大小，则substr函数抛出一个out_of_range异常。如果开始位置加上计数值大于string的大小，则substr会调整计数值，只拷贝到string的末尾。

| **表9.12: 子字符串操作** |  |
|:- |:- |
| s.substr(pos, n) | 返回一个string，包含s中从pos开始的n个字符的拷贝。pos的默认值为0.n的默认值为s.size() - pos，即拷贝从pos开始的所有字符

### 9.5.2 改变string的其他方法
string类型支持顺序容器的赋值运算符以及assign、insert和erase操作。除此之外，他还定义了额外的insert和erase版本。

出了接受迭代器的insert和erase版本外，string还提供了接受下标的版本。下标识出了开始删除的位置，或是insert到给定值之前的位置:

```c++
s.insert(s.size(), 5, '!');  // 在s末尾插入5个感叹号
s.erase(s.size() - 5, 5);  // 从s删除最后5个字符
```

标准库string类型还提供了接受C风格字符数组的insert和assign版本。例如，我们可以将以空字符结尾的字符数组insert到或assign给一个string:

```c++
const char *cp = "Stately, plump Buck";
s.assign(cp, 7);  // s == "Stately";
s.insert(s.size(), cp + 7);  // s == "Stately, plump Buck";
```

此处我们首先通过调用assign替换s的内容。我们赋予s的是从cp指向的地址开始的7个字符。要求赋值的字符必须小鱼或等于cp指向的数组中的字符数(不包括结尾的空字符)。

接下来在s上调用insert，我们的意图是将字符插入到s[size()]处元素之前的位置。在此列中，我们将cp开始的7个字符(至多到结尾空字符之前)拷贝到s中。

我们也可以指定将来自其他的string或子字符串的字符插入到当前string中赋予当前string:

```c++
string s = "some string", s2 = "some other string";
s.insert(0, s2);  // 在s中位置0之前插入s2的拷贝
s.insert(0, s2, 0, s2.size());  // 在s[0]之前插入到s2[0]开始的s2.size()个字符
```

### append和replace函数
string类定义了两个额外的成员函数: append和replace,这两个函数可以改变string的内容。表9.13描述了这两个函数的功能。append操作是在string末尾进行插入操作的一种简写形式:

```c++
string s ("C++ Primer"), s2 = s;  // 将s和s2初始化为"C++ Primer"
s.insert(s.size(), " 4th Ed.");  // s == “C++ Primer 4th Ed."
s2.append(" 4th Ed.");  // 等价方法：将" 4th Ed."追加到s2; s == s2;
```

replace操作是调用erase和insert的一种简写形式:

```c++
// 将"4th" 替换为”5th“的等价方法
s.erase(11, 3);  // s == "C++ Primer Ed."
s.insert(11, "5th");  // s == ”C++ Primer 5th Ed.";
// 从位置11开始，删除3个字符并插入“5th"
s2.replace(11, 3, "5th");
```

在此调用中，删除了3个字符，但在其位置插入了5个新字符。

| **表9.13: 修改string的操作** |  |
|:- |:- |
| s.insert(pos, args) | 在pos之前插入args指定的字符。pos可以是一个下标或一个迭代器。接受下标的版本返回一个指向s的引用；接受迭代器的版本返回指向第一个插入字符的迭代器 |
| s.erase(pos, len) | 删除从位置pos开始的len个字符。如果len被省略，则删除从pos开始直至s末尾的所有字符。返回一个指向s的引用 |
| s.assign(args) | 将s中的字符替换为args指定的字符。返回一个指向s的引用 |
| s.append(args) | 将args追加到s。返回一个指向s的引用 |
| s.replace(range, args) | 删除s中范围range内的字符，替换为args指定的字符。range或者是一个下标一个长度，或者是一对指向s的迭代器。返回一个指向s的引用 |
| args可以是下列形式之一;append和assign可以使用所有形式 |  |
| str不能鱼s相同，迭代器b和e不能指向s |  |
| str | 字符串str |
| str, por, len | str从pos开始最多len个字 |
| cp, len | 从cp指向的字符数组的前(最多)len个字符 |
| cp | cp指向的以空字符结尾的字符数组 |
| n,c | n个字符c |
| b, e | 迭代器b和e指定的范围内的字符 |
| 初始化列表 | 花括号包围的，以逗号分隔的字符列表 |

### 改变string的多种重载函数
表9.13列出的append、assign、insert和replace函数有多个重载版本。根据我们如何指定要添加的字符和string中被替换的部分，这些函数的参数有不同版本。幸运的是，这些函数有共同的接口。

assign和append函数无须指定要替换string中哪个部分：assign总是替换string中的所有内容，append总是将新字符追加到string末尾。

replace函数提供了两种删除元素范围的方式。可以通过一个位置和一个长度来指定范围，也可以用一个迭代器范围来指定。insert函数允许我们用两种方式指定插入点:用一个下标或一个迭代器。在两种情况下，新元素都会插入到给定下标(或迭代器)之前的位置。

可以用好几种方式来指定要添加到string中的字符。新字符可以来自于另一个string，来自于一个字符指针(指向的字符数组)，来自于一个花括号包围的字符列表，或者是一个字符和一个计数值。当字符来自于一个string或一个字符指针时，我们可以传递一个额外的参数来控制是拷贝部分还是全部字符。

并不是每个函数都支持所有形式的参数。例如，insert就不支持下标和初始化列表参数。类似的，如果我们希望用迭代器指定插入点，就不能用字符指针指定新字符的来源。