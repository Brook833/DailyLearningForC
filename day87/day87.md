2022.12.13



## 11.3.6 一个单词转换的map
我们将以一个程序结束本节的内容，它将展示map的创建、搜索以及遍历。这个程序的功能是这样的:给定一个string，将它转换为另一个string。程序的输入是两个文件。第一个文件保存的是一些规则，用来转换第二个文件的文本。每条规则由两部分组成:一个可能出现在输入文件的单词和一个用来替换它的短语。表达的含义是，每当第一个单词出现在输出中时，我闷就将它替换为对应的短语。第二个输入文件包含要转换的文本。

如果单词转换文件的内容如下所示:

```c++
brb be right bacl
k okay?
y why
r are
u you
pic picture
thk thanks!
18r later
```

我们希望转换的文本为:

```c++
where r u
y dont u send me a pic
k thk 18r
```

则程序应该生成这样的输出:

```c++
where are you
why dont you send me a picture
okay? thanks! later
```

### 单词转换程序
我们的程序将使用三个函数。函数word_transform管理整个过程。它接受两个ifstream参数:第一个参数应绑定到单词转换文件，第二个参数应绑定到我们要转换的文本文件。函数buildMap会读取转换规则文件，并创建一个map，用于保存每个单词到其转换内容的映射。函数transform接受一个string，如果存在转换规则，返回转换后的内容。

我们首先定义word_transform函数。最重要的部分时调用buildMap和transform:

```c++
void word_transform(ifstream &map_file, ifstream &input) {
    auto trans_map = buildMap(map_file);  // 保存转换规则
    string text;  // 保存输入中的每一行
    while (getline(input, text)) {  // 读取一行输入
        istringstream stream(text);  // 读取每个单词
        string word;
        bool firstword = true;  // 控制是否打印空格
        while (stream >> word) {
            if (firstword) {
                firstword = false;
            } else {
                cout << " ";  // 在单词间打印一个空格
            }
                // transform返回它第一个参数或其转换后的形式
            cout << transform(word, tras_map);  // 打印输出    
        }
        cout << endl;
    }
}
```

函数首先调用buildMap来生成单词转换的map，我们将它保存在trans_map中。函数的剩余部分处理输入文件。while循环用getline一行一行读取输入文件。这样做的目的是使的输出中的换行位置能与输入文件中一样。为了从每行中获取单词，我们使用了一个嵌套的while循环，他用一个istreamstream来处理当前行中的每个单词。

在输出过程中，内层while使用一个bool遍历firstword来确定是否打印一个空格。它通过调用transform来获得要打印的单词。transform的返回值或者是word中原来的string,或者是trans_map中指出的对应的转换内容。

### 建立转换映射
函数buildMap读取给定文件，建立转换映射:

```c++
map<string, string> buildMap(ifstream &map_file) {
    map<string, string> trans_map;  // 保存转换规则
    string key;  // 要转换的单词
    string value;  // 替换后的内容
    // 读取第一个单词存入key中，行中剩余内容存入value。
    while (map_file >> key && getline(map_file, value)) {
        if (value.size() > 1) {  // 检查是否有转换规则
            trans_map[key] = value.substr(1);  // 跳过前导空格
        } else {
            throw runtime_error("no rule for " + key);
        }
        return trans_map;
    }
}
```

map_file中的每一行对应一条规则。每条规则由一个单词和一个短语组成，短语可能包含多个单词。我们用>>读取要转换的单词,存入key中，并调用getline读取这一行中的剩余内容存入value。由于getline不会跳过前导空格，需要我们来跳过单词和它的转换内容之间的空格。在保存转换规则之前，检查是否获得了一个以上的字符。如果是，调用substr来跳过分隔单词及其转换短语之间的前导空格，并将得到的子字符串存入trans_map。

注意，我们使用下标运算符来添加关键字-值对。我们隐含地忽略了一个单词在转换中出现多次的情况。如果真的由单词出现多次，循环会将最后一个对应短语存入trans_map。当while循环结束后，trans_map中将保存着用来转换输入文本的规则。

### 生成转换文本
函数transform进行实际的转换工作。其参数是需要转换的string的引用和转换规则map。如果给定string在map中，transform返回相应的短语。否则，transform直接返回原string:

```c++
const string& transform(const string &s, const map<string, string> &m) {
    // 实际的转换工作;此部分是程序的核心
    auto map_it = m.find(s);
    // 如果单词在转换规则mao中
    if (map_it != m.cend()) {
        return map_it->second;  // 使用替换短语
    } else {
        return s;  // 否则返回原string
    }
}
```

函数首先调用find来确定给定string是否在map中。如果存在，则find返回一个指向对应元素的迭代器。否则，find返回尾后迭代器。如果元素存在，我们解引用迭代器，获得一个保存关键字和值的pair，然后返回成员second，即用来替代s的内容。

## 11.4 无序容器
新标准定义了4个无序关联容器。这些容器不是使用比较运算符来组织元素，而是使用一个哈希函数和关键字类型的==运算符。在关键字类型的元素没有明显的序关系的情况下，无序容器是非常有用的。在某些应用中，维护元素的序代价非常高昂，此时无序容器也很有用。

虽然理论上哈希技术能获得更好的平均性能，但在实际测试中想要达到很好的效果还需要进行一些性能测试和调优工作。因此，使用无序容器通常更为简单(通常也会有更好的性能)。

==Tip:如果关键字类型固有就是无序的，或者性能测试发现问题可以用哈西技术解决，就可以使用无序容器==

### 使用无序容器
除了哈希管理操作之外，无序容器还提供了与有序容器相同的操作(find、insert等)。这意味着我们曾用于map和set的操作也能用于unordered_map和unordered_set。类似的，无序容器也有允许重复关键字的版本。

因此，通常可以用一个无序容器替换对应的有序容器，反之亦然。但是，由于元素未按顺序存储，一个使用无序容器的程序的输出(通常)会和使用有序容器的版本不同。

例如，可以用unordered_map重写最初的单词计数程序:

```c++
// 统计出现次数，但单词不会按字典序排列
unordered_map<string, size_t> word_count;
string word;
while (cin >> word) {
    ++word_count[word];
}
for (const auto c : word_count) {
    cout << w.first << " occurs " << w.second << ((w.second > 1) ? " times" : " time" << endl;
}
```

此程序与原程序的唯一区别是word_count的类型。对于每个单词，我们将得到相同的计数结果。但单词不太可能按字典序输出。

### 管理桶
无序容器在存储上组织为一组桶，每个桶保存零个或多个元素。无序容器使用一个哈希函数将元素映射到桶。为了访问一个元素，容器首先计算元素的哈希值，它指出应该搜索哪个桶。容器将具有一个特定哈希值的所有元素都保存在相同的桶中，如果容器允许重复关键字，所有具有相同关键字的元素也都会在同一个桶中。因此，无序容器的性能依赖于哈希函数的质量和桶的数量和大小。

对于相同的参数，哈希函数必须总是产生相同的结果。理想情况下，哈希函数还能讲每个特定的值映射到唯一的桶。但是，将不同关键字的元素映射到相同的桶也是允许的。当一个桶保存多个元素时，需要顺序搜索这些元素来插着我们想要的那个。计算一个元素的哈希值和在铜钟搜索通常都是很快的操作。但是,如果一个桶中保存了很多元素，那么查找一个特定元素的就需要大量比较操作。

无序容器提供了一组管理桶的函数，如表11.8所示。这些成员函数允许我们查询容器的状态以及在必要时强制容器进行重组。

| **表11.8: 无序容器管理操作** |  |
|:- |:- |
| 桶接口 |  |
| c.bucket_count() | 正在使用的桶的数目 |
| c.max_bucket_count() | 容器能容纳的最多的桶的数目 |
| c.bucket_size(n) | 第n个桶中有多少个元素 |
| c.bucket(k) | 关键字为k的元素在哪个桶中 |
| 桶迭代 |  |
| local_iterator | 可以用来访问桶中元素的迭代器类型 |
| const_local_iterator | 桶迭代器的const版本 |
| c.begin(n), c.end(n) | 桶n的首元素迭代器和尾后迭代器 |
| c.cbegin(n), c.cend(n) | 与前两个函数类似，但返回const_local_iterator |
| 哈希策略 |
| c.load_factor() | 每个桶的平均元素数量，返回float值 |
| c.max_load_factor() | c试图维护平均桶的大小，返回float值。c会在需要时添加新的桶，以使得load_factro<=max_load_factor |
| c.rehash(n) | 重组存储，以使得bucket_count>=n且bucket_count > size/max_load_factor |
| c.reserve(n) | 重组存储，使得c可以保存n个元素且不必rehash |

### 无序容器对关键字类型的要求
默认情况下，无序容器使用关键字类型的==运算符来比较元素，它们还是用一个hash<key_type>类型的对象来生成每个元素的哈希值。标准库为内质类型(包括指针)提供了hash模板。还为一些标准库类型，包括string和我们将要在第12章介绍的智能指针类型定义了hash。因此，我们呢可以直接定义关键字是内置类型(包括指针类型)、string还是智能指针类型的无序容器。

但是，我们不能直接定义关键字类型为自定义类类型的无序容器。与容器不同，不能直接使用hash模板，而必须提供我们自己的hash模板版本。我们将在16.5节中介绍如何做到这一点。

我们不使用默认的hash，而是使用另一种方法，类似于为有序容器重载关键字类型的默认比较操作。为了能将Sale_data用作关键字，我们需要提供函数还替代==运算符和哈希值计算函数。我们从定义这些重载函数开始:

```c++
size_t hasher(const Sales_data &sd) {
    return hash<string>()(sd.isbn());
}
bool eqOp(const Sales_data &lhs, const Sales_data &rhs) {
    return lhs.isbn() == rhs.isbn();
}
```

我们的hasher函数使用一个标准库hash类型对象来计算ISBN成员的哈希值，该hash类型建立在string类型之上。类似的，eqOp函数通过比较ISBN号来比较两个Sales_data。

我们使用这些函数来定义一个unordered_multiset:

```c++
usingSD_multiset = unordered_multiset<Sales_data, decltype(hasher)*, decltype(eqOp)*>;
// 参数是桶大小、哈希函数指针和相等性判断运算符指针
SD_multiset bookstore(42, hasher, eqOp);
```

为了简化bookstore的定义，首先为unordered_multiset定义了一个类型别名，此集合的哈希和相等性判断操作与hasher和eqOph函数有着相同的类型。通过使用这种类型，在定义bookstore时可以将我们希望它使用的函数的指针传递给他。

如果我们的类定义了==运算符，则可以只重载哈希函数:

```c++
// 使用FooHash生成哈希值；Foo必须有==运算符
unordered_set<Foo, decltype(FootHash)*> fooSet(10, FooHash);