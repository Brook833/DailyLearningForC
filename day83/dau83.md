2022.12.09



## 11.3.2 添加元素
关联容器的insert成员向容器中添加一个元素或一个元素范围。由于map和set(以及对应的无序类型)包含不重复的关键字，因此插入一个已存在的元素对容器没有任何影响:

```c++
vector<int> ivec = {2, 4, 6, 8, 2, 4, 6, 8};  // ivec有8个元素
set<int> set2;  // 空集合
set2.insert(ivec.cbegin(), ivec.cend());  // set2有4个元素
set2.inseert({1, 3, 5, 7, 1, 3, 5, 7});  // set2现在有8个元素
```

insert有两个版本，分别接受一对迭代器，或是一个初始化器列表，这两个版本的行为类似对应的构造函数————对于一个给定的关键字，只有第一个带此关键字的元素才会被插入到容器中。

### 向map添加元素
对一个map进行insert操作时，必须记住元素类型是pair。通常，对于想要插入的数据，并没有一个现成的pair对象。可以在insert的参数列表中创建一个pair:

```c++
// 向word_count插入word的4种方法
word_count.insert({word, 1});
word_count.insert(pair<string, size_t>(word, 1));
word_count.insert(make_pair(word, 1));
word_count.insert(map<string, size_t>::value_type(word, 1));
```

如我们所见，在新标准下，创建一个pair最简单的方法是在参数列表中使用花括号初始化。也可以调用make_pair或显式构造pair。最后一个insert调用中的参数:

```c++
map<string, size_t>::value_type (s, 1);
```

构造一个恰当的pair类型，并构造该类型的一个新对象，插入到map中。

| **表11.4: 关联容器insert操作** |  |
| c.insert(v) | v是value_type类型的对象;args用来构造一个元素 |
| c.emplace(args) | 对于map和set，只有当元素的关键字不在c中时才插入(或构造)元素。函数返回一个pair，包含一个迭代器，指向具有指定关键字的元素，以及一个指示是否成功的bool值。对于multimap和multiset，也总会插入(或构造)给定元素，并返回一个指向新元素的迭代器。|
| c.insert(b, e) | b和e实迭代器，表示个c::value_type类型值的范围 |
| c.insert(i1) | i1是这种值的花括号列表。函数返回void |
|  | 对于map和set，只插入关键字不在c中的元素。对于multimap和multiset，则会插入范围中的每个元素 |
| c.insert(p, v) | 类似insert(v)(或emplace(args)),但迭代器p作为一个指示，之处从哪里开始搜索新元素应该存储的位置。返回一个迭代器，指向具有给定关键字的元素。 | 