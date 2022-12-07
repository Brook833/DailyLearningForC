2022.12.07



## 11.2.3 pair类型
在介绍关联容器操作之前，我们需要了解名为pair的标准库类型，它定义在头文件utility中。

一个pair保存两个数据成员。类似容器，pair是一个用来生成特定类型的模板。当创建一个pair时，我们必须提供两个类型名，pair的数据成员将具体对应的类型。两个类型不要求一样:

```c++
pair<string, string> anon;  // 保存两个string
pair<string, size_t> word_count;  // 保存一个string和一个size_t
pair<string, vector<int>> line;  // 保存一个string和vector<int>
```

pair的默认构造函数对数据成员进行值初始化。因此，anon是一个包含两个空string的pair，line保存一个空string和一个空vector。word_count中的size_t成员值为0，而string成员被初始化为空。

我们也可以为每个成员提供初始化器。

```c++
pair<string, string> author{"James", "Joyce"};
```

这条语句创建一个名为author的pair，两个成员被初始化为"James"和"Joyce"。

与其他标准库类型不同，pair的数据成员是public的。两个成员分别命名为first和second。我们用普通的成员访问符号来访问它们，例如:

```c++
cout << w.first << " occurs " << w. second << ((w.second) > 1) ? " times" : " time" << endl;
```

此处，w是指向map中某个元素的引用。map的元素pair。在这条语句中，我们首先打印关键字————元素的first成员，接着打印计数器————second成员。标准库只定义了几个有限的pair操作，表11.2列出了这些操作。

| **表11.2: pair上的操作** |  |
| pair<T1, T2> p; | p是一个pair，两个类型分别为T1和T2的成员函数都进行了值初始化。 |
| pair<T1, T2> P(v1, v2) | p是一个成员类型为T1和T2和pair;first和second成员分别用v1和v2进行初始化 |
| pair<T1, T2> p = (v1, v2); | 等价于p(v1, v2) |
| nake_pair(v1, v2) | 返回一个用v1和v2初始化的pair。pair的类型从v1和v2的类型推断出来 |
| p.first | 返回p的名为first的(公有)数据成员 |
| p.second | 返回p的名为second的(公有)数据成员 |
| p1 relop p2 | 关系运算符(<、>、<=、>=)按字典序定义:例如，当p1.first < p2.first 或!(p2.first < p1.first) && p1.second < p2.second 成立时，p1 < p2为true。关系运算利用元素的<运算符来实现。 |
| p1 == p2 | 当first和second成员分别相等时，两个pair相等。相等性判断利用元素的==运算符实现。 |
| p1 != p2 |  |

### 创建pair对象的函数
想象有一个函数需要返回一个pair。在新标准下，我们可以对返回值进行列表初始化:

```c++
pair<string, int>
processs(vector<string> &v) {
    // 处理v
    if (!v.empty()) {
        return {v.back(), v.back().size()};  // 列表初始化
    } else {
        return pair<string, int>();  // 隐式构造返回值
    }
}
```

若v不为空，我们返回一个由v中最后一个string及其大小组成的pair。否则，隐式构造一个空pair，并返回它。

在较早的C++版本中，不允许用花括号包围的初始化器来返回pair这种类型的对象，必须显式构造返回值:

```c++
if (!v.empty()) {
    return pair<string, int>(v.back(), v.back().size());
}
```

我们还可以用make_pair来生成pair对象，pair的两个类型来自于make_pair的参数:

```c++
if (!v.empty()) {
    return make_pair(v.back(), v.back().size());
}
```







