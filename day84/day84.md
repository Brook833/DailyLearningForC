2022.12.10



### 检测insert的返回值
insert(或emplace)返回的值依赖于容器类型和参数。对于不包含重复关键字的容器，添加单一元素的insert和empalce版本返回一个pair，告诉我们插入操作是否成功。pair的first成员是一个迭代器，指向具有给定关键字的元素；second成员是一个bool值，指出元素是插入成功还是已经存在于容器中。如果关键字已在容器中，则insert什么事情也不做，且返回值中的bool部分为false。如果关键字不在，元素被插入容器中，且bool值为true。

作为一个例子，我们用insert重写单词计数程序:

```c++
// 统计每个单词在输入中出现次数的一种更繁琐的方法
map<string, size_t> word_count;  // 从string到size_t的空map
string word;
while (cin >> word) {
    // 插入一个元素，关键字等于word，值为1；
    // 若word已在word_count中，insert什么也不做
    auto ret = word_count.insert({word, 1});
    if (!ret.second) {  // word已在word_count中
        ++ret.first->second;  // 递增计数器
    }
}
// 简单方法
while (cin >> word) {
    ++word_count[word];
}
```

对于每个word，我们尝试将其插入到容器中，对应的值为1。若word已在map中，则什么都不做，特别是与word相关联的计数器的值不变。若word还未在map中，则此string对象被添加到map中，且其计数器的值被置为1。

if语句检查返回值的bool部分，若为flase，则表明插入操作未发生。在此情况下，word已存在与word_count中，因此必须递增元素所关联的计数器。

### 展开递增语句
在这个版本的单词计数程序中，递增计数器的语句很难理解。通过添加一些括号来反映出运算符的优先级，会使表达式更容易理解一些:

```c++
++((ret.first)->second);  // 等价的表达式
```

ret保存insert返回的值，是一个pair。
ret.first是pair的第一个成员，是一个map迭代器，指向具有给定关键字的元素。
ret.first->解引用此迭代器，提取map中的元素，元素也是一个pair。
ret.first->second map中元素的值的部分。
++ret.first->second 递增此值。

再回到原来完整的递增语句，它提取匹配关键字word的元素的迭代器，并递增与我们试图插入的关键字相关联的计数器。

如果读者使用的是旧版本编译器。或者是在阅读新标准推出之前编写的代码，ret的声明和初始化可能复杂些。

```c++
pair<map<string, size_t>::iterator, bool> ret = word_count.insert(make_pair(word, 1));
```

### 向multiset或multimap添加元素
我们的单词计数程序依赖于这样一个事实：一个给定的关键字只能出现一次。这样，任意给定的单词只有一个关联的计数器。我们有时希望能添加相同关键字的多个元素。例如，可能想建立作者到他所著书籍题目的映射。在此情况下，每个作者可能有多个条目，因此我们呢应该使用multimap而不是map。由于一个multi容器的关键字不必唯一，在这些类型上调用insert总会插入一个元素:

```c++
multimap<string, string> authors;
// 插入第一个元素，关键字为Barth, John
authors.insert({"Barth, John", "Sot-Weed Factor"});
// 正确:添加第二个元素，关键字也是Barth, John
authors.insert({"Barth, John", "Lost in the Funhouse"});
```

对允许重复关键字的容器，接受单个元素的insert操作返回一个指向新元素的迭代器。这里无需返回一个Bool值，因为insert总是向这类容器中加入一个新元素。

## 11.3.3 删除元素
关联容器定义了三个版本的erase,如表11.5所示。与顺序容器一样，我们可以通过传递给erase一个迭代器或一个迭代器对来删除一个元素或一个元素范围。这两个版本的erase与对应顺序容器的操作非常相似: 指定的元素被删除，函数返回void。

关联容器提供一个额外的erase操作，它接受一个key_type参数。此版本删除所有匹配给定关键字的元素(如果存在的话)，返回实际删除的元素的数量。我们可以用此版本在打印结果之前从word_count中删除一个特定的单词:

```c++
// 删除一个关键字，返回删除的元素数量
if (word_count.erase(removal_word)) {
    cout << "ok: " << removal_word << " removed\n";
} else {
    cout << "oops: " << removal_word << " not found!\n";
}
```

对于保存不重复关键字的容器，erase的返回值总是0或1。若返回值为0，则表明想要删除的元素并不在容器中。

对允许重复关键字的容器，删除元素的数量可能大于1:

```c++
auto cnt = authors.erase("Barth, John");
```

如果autors是上节的multimap，则cnt的值为2。

| **表11.5: 从关联容器删除元素** |  |
|:- |:- |
| c.erase(k) | 从c中删除关键字为k的元素。返回一个size_type值，指出删除的元素的数量 |
| c.erase(p) | 从c中删除迭代器p指定的元素。p必须指向c中一个真实元素，不能等于c.end()。返回一个指向p之后元素的迭代器，若p指向c中的尾元素，则返回c.end()。 |、
| c.erase(b, e) | 删除迭代器对b和e所表示的范围中的元素。返回e |

## 11.3.4 map的下标操作
map和unordered_map容器提供了下标运算符和一个对应的at函数，如表11.6所示。set类型不持支下标，因为set中没有与关键字相关联的"值"。元素本身就是关键字，因此"获区与一个关键字相关联的值"的操作就没有意义了。我们不能对一个multimap或一个unordered_multimap进行下标操作，因为这些容器中可能有多个值与一个关键字相关联。

类似我们用过的其他下标运算符，map下标运算符接受一个索引(即，一个关键字)，获取与此关键字相关联的值。但是，与其他下标运算符不同的是，如果关键字并不在map中，会为它创建一个元素并插入到map中，关联值将进行值初始化。

例如，如果我们编写如下代码:

```c++
map<string, size_t> word_count;  // empty map
// 插入一个关键字为Anna的元素，关联之进行值初始化;然后将1赋予它。
word_count["Anna"] = 1;
```

将会执行如下操作:
> + 在word_count中搜索关键字为Anna的元素，未找到。
> + 将一个新的关键字-值对插入到word_count中。关键字是一个const string，保存Anna。值进行值初始化，在本例中意味着值为0。
> + 提取出新插入的元素，并将值1赋予它。

由于下标运算符可能插入一个新元素，我们呢只可以对非const的map使用下标操作。

**Note:对一个map使用下标操作，其行为与数组或vector上的下标操作很不相同:使用一个不在容器中的关键字作为下标，会添加一个具有此关键字的元素到map中。**

| **表11.6: map和unordered_map的下标操作** |  |
|:- |:- |
| c[k] | 返回关键字为k的元素:如果k不在c中，添加一个关键字为k的元素，对其进行值初始化 |
| c.at(k) | 访问关键字为k的元素，带参数检查；若k不在c中，抛出一个out_of_range异常 |

### 使用下标操作的返回值
map的下标运算符与我们用过的其他下标运算符的另一个不同之处是其返回类型。通常情况下，解引用一个迭代器所返回的类型与下标运算符返回的类型是一样的。但对map则不然: 当对一个map进行下标操作时，会获得一个mapped_type对象；但当解引用一个map迭代器时，会得到一个value_type对象。

与其他下标运算符相同的是，map的下标运算符返回一个左值。由于返回的是一个左值，所以我们既可以读也可以写元素:

```c++
cout << word_count["Anna"];  // 用Anna作为下标提取元素；会打印出1
++word_count["Anna"];  // 提取元素，将其+1
cout << word_count["Anna"];  // 提取元素并打印，2。
```

如果关键字还未在map中，下标运算符会添加一个新元素，这一特性允许我们编写出异常简介的程序，例如单词计数程序中的循环。另一方面，有时只是想知道一个元素是否已在map中，但在不存在时并不想添加元素。在这种情况下，就不能使用下标运算符。
