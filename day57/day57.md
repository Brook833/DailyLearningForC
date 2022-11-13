2022.11.13



## 9.3 顺序容器操作
顺序容器和关联容器的不同之处在于两者组织元素的方式。这些不同之处直接关系到了元素如何存储、访问、添加以及删除。上一届介绍了所有元气都支持的操作。本章剩余部分将介绍顺序容器所有支持的操作。

## 9.3.1 向顺序容器添加元素
除array外，所有标准库容器都提供灵活的内存管理。在运行时可以动态添加或删除元素来改变容器大小。表9.5列出了向顺序容器(非array)添加元素的操作。

| **表9.5: 向顺序容器添加元素的操作** |  |
| :- | :- |
| 这些操作会改变容器的大小；array不支持这些操作 |  |
| forward_list 有自己专有版本的insert和emplace |  |
| forward_list不支持push_back和emplace_back |  |
| vector 和 string 不支持push_front和emplace_front |  |
| c.push_back(t) 或 c.emplace_back(args) | 在c的尾部创建一个值为t或args创建的元素。返回void |
| c.push_front(t) 或 c.emplace_back(args) | 在c的头部创建一个值为t或由args创建的元素。返回void |
| c.insert(p, t) 或 c.emplace(p, args) | 在迭代器p指向的元素之前创建一个值为t或由args创建的元素。返回指向新添加的元素的迭代器 |
| c.insert(p, n, t) | 在迭代器p指向的元素之前插入n个值为t的元素。返回指向新添加的第一个元素的迭代器；若n为0，则返回p |
| c.insert(p, b, e) | 将迭代器b和e指定的范围内的元素插入迭代器p指向的元素之前。b和e不能指向c中的元素。返回指向新添加的第一个元素的迭代器；若范围为空，则返回p |
| c.insert(p, i1) | i1是一个花括号包围的元素值列表。将这些给定值插入到迭代器p指向的元素之前。返回指向新添加的第一个元素的迭代器；若列表为空，则返回p |

**WARNING: 向一个vector、string或deque插入元素会使所有指向容器的迭代器、引用和指针失效**

当我们使用这些操作时，必须记得不同容器使用不同的策略来分配元素空间，而这些策略直接影响性能。在一个vector或string的尾部之外的任何位置，或是一个deque的首尾之外的任何位置添加元素，都需要移动元素。而且，向一个vector或string添加元素可能引起整个对象存储空间的重新分配。重新分配一个对象的存储空间需要分配新的内存，并将元素从旧的空间移动到新的空间中。

### 使用push_back
除array和forward_list之外，每个顺序容器(包括string类型)都支持push_back。

例如，下面的循环每次读取一个string到word中，然后追加到容器尾部：

```c++
// 从标准输入读取数据，将每个单词放到容器末尾
string word;
while (cin >> word)
    container.push_back(word);
```

对push_back的调用在container尾部创建了一个新的元素，将container的size增大了1。该元素的值为word的一个拷贝。container的类型可以是list、ector或deque。

由于string是一个字符容器，我们也可以用push_back在string末尾添加字符：
```c++
void pluralize(size_t cnt, string &word) {
    if (cnt > 1) {
        word.push_back('s');  // 等价于word += 's'
    }
}
```

**关键概念: 容器元素是拷贝**
当我们用一个对象来初始化容器时，或将一个对象插入到容器中时，实际上放入到容器中的对象值的一个拷贝，而不是对象本身。就像我们将一个对象传递给非引用参数一样，容器中的元素与提供值的对象之间没有任何关联。随后对容器中元素的任何改变都不会影响到原始对象，反之亦然。

### 使用push_front
除了push_back,list,forward_list和deque容器还支持名为push_front的类似操作。此操作将元素插入到容器头部:

```c++
list<int> ilist;
// 将元素添加到ilist开头
for (size_t ix = 0; ix != 4; ++ix) {
    ilist.push_front(ix);
}
```
此循环将元素0、1、2、3添加到ilist头部。每个元素都插入到list的新的开始位置(new beginning)。即，当我们插入1时，它会被放置在0之前，2被放置在1之前，依此类推。因此，在循环中以这种方式将元素添加到容器中，最终会形成逆序。在循环执行完毕后，ilist保存序列3、2、1、0。

注意，deque像vector一样提供了随机访问元素的能力，但它提供了vector所不支持的push_front。deque保证在容器首尾进行插入和删除元素的操作都只花费常数时间。与vector一样，在deque首位之外的位置插入元素会很耗时。

### 在容器中的特定位置添加元素
push_back和push_front操作提供了一种方便的在顺序容器尾部或头部插入单个元素的方法。insert成员提供了更一般的添加功能，它允许我们在容器中任意位置插入0个或多个元素。vector、deque、list和string都支持insert成员。forward_list提供了特殊版本的insert成员。

每个insert函数都接受一个迭代器作为其第一个参数。迭代器指出了在容器中什么位置放置元素。它可以接受容器中任何位置，包括容器尾部之后的下一个位置。由于迭代器可能指向容器尾部之后不存在的元素的位置，而且在容器开始位置插入元素时很有用的功能，所以insert函数将元素插入到迭代器所指定的位置之前。例如，下面的语句：

```c++
slist.insert(iter, "Hello!");  // 将"Hello!"添加到iter之前的位置
```

将一个值为"Hello"的string插入到iter指向的元素之前的位置。

虽然某些容器不支持push_front操作，但它们对于insert操作并无类似的限制(插入开始位置)。因此我们可以将元素插入到容器的开始位置，而不必担心容器是否支持push_front：

```c++
vector<string> svec;
list<string> slist;
// 等价于调用slist.push_front("Hello!");
slist.insert(slist.begin(), "Hello!");

// vector不支持push_front,但我们可以插入到begin()之前
// 警告: 插入到vector末尾之外的任何位置都可能很慢
svec.insert(svec.begin(), "Hello!");
```

**WARNING: 将元素插入到vector、deque和string中的任何位置都是合法的。然而，这样做可能很耗时**

### 插入范围内元素
除了第一个迭代器参数之外，insert函数还可以接受更多的参数，这与容器构造函数类似。其中一个版本接受一个元素数目和一个值，它将指定数量的元素添加到指定位置之前，这些元素都按给定值初始化。

```c++
svec.insert(svec.end(), 10, "Anna");
```

这行代码将10个元素插入到svec的末尾，并将所有元素都初始化为string "Anna"。

接受一对迭代器或一个初始化列表的insert版本将给定范围中的元素插入到指定位置之前：

```c++
vector<string> v = {"quasi", "simba", "frollo", "scar"};
// 将v的最后两个元素添加到slist的开始位置
slist.insert(slist.begin(), v.end()-2, v.end());
slist.insert(slist.end(), {"these", "words", "will", "go", "at", "the", "end"});
```

如果我们传递给insert一对迭代器，它们不能指向添加元素的目标容器。

在新标准下，接受元素个数或范围insert版本返回指向第一个新加入元素的迭代器。如果范围为空，不插入任何元素，insert操作会将第一个参数返回。

### 使用insert的返回值

通过使用insert的返回值，可以在容器中一个特定位置反复插入元素:

```c++
list<string> 1st;
auto iter = 1st.begin();
while (cin >> word) {
    iter = 1st.insert(iter, word);  // 等价于调用push_front
}
```

**Note: 理解这个循环是如何工作的非常重要，特别是理解这个循环为什么等价于push_front尤为重要**

在循环之前，我们将iter初始化为1st.begin()。第一次调用insert会将我们刚刚读入的string插入到iter所指向的元素之前的位置。insert返回的迭代器恰好指向这个新元素。我们将此迭代器赋予iter并重复循环，读取下一个单词。只要继续有单词读入，每步while循环就会将一个新元素插入到iter之前，并将iter改变为新加入元素的位置。此元素为(新的)首元素。因此，每步循环将一个新元素插入到list首元素之前的位置。

### 使用emplace操作
新标准引入了三个新成员——emplace_front、emplace和emplace_back,这些操作构造而不是拷贝元素。这些操作分别对应push_front、insert和push_back，允许我们将元素放置在容器头部、一个指定位置之前或容器尾部。

当调用push或insert成员函数时，我们将元素类型的对象传递给它们，这些对象背靠背到容器中。而当我们调用一个emplace成员函数时，则是将参数传递给元素类型的构造函数。empalce成员使用这些参数在容器管理的内存空间中直接构造元素。例如，假定c保存Sales_data元素：

```c++
// 在c的末尾构造一个Sales_data对象
// 使用三个参数的Sales_data构造函数
c.emplace_back("978-0590353403", 25, 15.99);
// 错误，没有接受三个参数的push_back版本
c.push_bakc("978-0590353403", 25, 15.99);
// 正确:创建一个临时的Sales_data对象传递给push_back
c.push_back(Sales_data("978-0590353403", 25, 15,99));
```

其中对emplace_back的调用和第二个push_back调用都会创建新的Sales_data对象。在调用emplace_back时，会在容器管理的内存空间中直接创建对象。而调用push_back则会创建一个局部临时对象，并将其压入容器中。

emplace函数的参数根据元素类型而变化，参数必须于元素类型的构造函数相匹配：

```c++
// iter指向c中一个元素，其中保存了Sales_data元素
c.emplace_back();  // 使用Sales_data的默认构造函数
c.emplace(iter, "999-999999999");  // 使用Sales_data(string)
//使用Sales_data的接受一个ISBN、一个count和一个price的构造函数
c.emplace_front("978-0590353403", 25, 15,99);
```

**Note: emplace函数在容器中直接构造函数。传递给emplace函数的参数必须与元素类型的构造函数相匹配**
